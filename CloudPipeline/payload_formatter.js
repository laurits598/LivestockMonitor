function decodeUplink(input) {
  const bytes = input.bytes || [];

  // Convert bytes to ASCII
  let text = "";
  for (let i = 0; i < bytes.length; i++) {
    if (bytes[i] !== 0) {
      text += String.fromCharCode(bytes[i]);
    }
  }

  // Format:
  // <flag>:<event>
  // E.g.
  // T:23.5
  // W:FALL_DETECTED

  const type = text.charAt(0);
  const payload = text.substring(2); // everything after "X:"

  let out = { raw_text: text };

  switch (type) {
    case "T":
      out.temperature = parseFloat(payload);
      break;

    case "W":
      out.warning = payload;
      break;

    case "S":
      out.status = payload;
      break;

    default:
      return {
        data: { raw_text: text },
        warnings: ["Unknown payload type"]
      };
  }

  return { data: out };
}
