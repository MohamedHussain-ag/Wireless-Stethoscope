import asyncio
import websockets
import wave
import struct


steth_reading = "steth_beat.wav"
steth_recording = wave.open(steth_reading, 'wb')
steth_recording .setnchannels(1)
steth_recording .setsampwidth(2)
steth_recording .setframerate(16000)

async def handle_audio(websocket, path):
    print("Chest- piece connected")
    try:
        async for message in websocket:
            if isinstance(message, bytes):
                wav_file.writeframes(message)
                print(f"Received DATA: {len(message)} bytes")
    except websockets.ConnectionClosed as e:
        print("Chest-Piece disconnected:", e)
    finally:
        steth_recording .close()
        print("Record saved to", steth_reading)

async def main():
    async with websockets.serve(handle_audio, '192.168.43.160', 8090):
        print("web Server running on: 192.168.43.160:8090")
        await asyncio.Future()

asyncio.run(main())
