from shapely.geometry import Polygon, Point 
from fastapi import FastAPI
from fastapi.staticfiles import StaticFiles
from fastapi.responses import HTMLResponse
from pydantic import BaseModel
from typing import List, Tuple
import os

app = FastAPI() 

# gets the current directory 
this_dir = os.path.dirname(os.path.abspath(__file__))

# mounts index.html on endpoint /ui 
app.mount("/ui", StaticFiles(directory=this_dir, html=True), name="ui")

class Coordinates(BaseModel):
    longitude: float 
    latitude: float

farm_coords: List[Tuple[float, float]] = []
gps_coords: List[Tuple[float, float]] = []

# endpoint for receiving coordinates from the UI and returns a message
@app.post("/coordinates")
async def give_coordinates(coords: List[Coordinates]):
    for coord in coords: 
        farm_coords.append((coord.longitude, coord.latitude))
    return {"message": f"{len(coords)} coordinates received"}

# endpoint for receiving gps coordinates from the collar
@app.post("/gps")
async def gps_coordinates(coords: List[Coordinates]):
    for coord in coords: 
        gps_coords.append((coord.longitude, coord.latitude))
    return {"message": f"{len(coords)} coordinates received"}

# endpoint for getting the status of geo-fencing as a html page 
@app.get("/status", response_class=HTMLResponse)
async def get_status():

    # https://b0uh.github.io/python-geofencing.html
    farm = Polygon(farm_coords)
    horse = Point(12.31320682, 55.47257823)  # hardcoded animal position
    status = farm.contains(horse)

    if status:
        message = "The animal is in the farm"
    else: 
        message = "Alert: The animal is outside of the farm"

    # status page that displays the status of the animal 
    # check index.html for html references 
    html_content = f"""
    <!DOCTYPE html>
    <html>
    <head>
        <style>
            body {{
                margin: 0;
                background-color: rgb(111, 89, 89);
                font-family: Arial, sans-serif;
                text-align: center;
                color: white;
            }}
            .container {{
                margin-top: 20%;
            }}
            input {{
                padding: 10px;
                border: none;
                border-radius: 5px;
                font-size: 16px;
            }}
            input[type="text"] {{
                width: 260px;
                margin-bottom: 15px;
            }}
            input[type="submit"] {{
                background-color:rgb(56, 52, 52);
                color: white;
                cursor: pointer;
            }}
        </style>
    </head>

    <body>
        <div class="container">
            <h1>My Animals</h1>
            <h2>{message}</h2>
        </div>
    </body>
    </html>
    """
    return HTMLResponse(content=html_content)





   






