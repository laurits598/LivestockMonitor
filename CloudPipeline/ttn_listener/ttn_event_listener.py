import os
import asyncio
import datetime
import json
import subprocess
from azure.eventhub.aio import EventHubConsumerClient

EVENT_HUB_CONN_STR = "Endpoint=X;SharedAccessKeyName=X;SharedAccessKey=X;EntityPath=X"
EVENT_HUB_NAME = "X"

LOG_DIR = "../logs"
os.makedirs(LOG_DIR, exist_ok=True)

async def on_event(partition_context, event):
    try:
        data = event.body_as_json()
    except Exception:
        data = json.loads(event.body_as_str())

    # Only keep decoded_payload
    uplink = data.get("uplink_message", {})
    decoded = uplink.get("decoded_payload", {})

    # Build the log line: timestamp + decoded dict
    log_line = f"T: {datetime.datetime.utcnow().isoformat()} {decoded}"
    print(log_line)

    # Append to log file - could be changed to a database for future work
    log_file = os.path.join(LOG_DIR, f"iot_messages_{partition_context.partition_id}.log")
    with open(log_file, "a", encoding="utf-8") as f:
        f.write(log_line + "\n")
        # Check if the flag signals a warning
        if decoded.get("raw_text", "").startswith("W:") and "warning" in decoded:
            extra_line = f"Received warning, Event: {decoded['warning']}"
            print(extra_line)
            f.write(extra_line + "\n")
            #event = str(extra_line)

            # Run a mosqtuitto publish command to publish with MQTT. In this instance its to the ESP32.
            subprocess.run(f'mosquitto_pub -h localhost -p 1883 -u esp32 -P esp32-ok -t test/topic -m "WARNING"', shell=True)

    await partition_context.update_checkpoint(event)

async def main():
    client = EventHubConsumerClient.from_connection_string(
        conn_str=EVENT_HUB_CONN_STR,
        consumer_group="$Default",
        eventhub_name=EVENT_HUB_NAME
    )
    async with client:
        await client.receive(on_event=on_event, starting_position="-1")

if __name__ == "__main__":
    asyncio.run(main())