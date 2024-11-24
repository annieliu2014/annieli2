#!/usr/bin/python3
import argparse
import socket

parser = argparse.ArgumentParser(description="solve script for 'Riddle Me This'")
parser.add_argument("--host", default="challenge", help="the host for the instance")
parser.add_argument("--port", type=int, default=5000, help="the port of the instance")
parser.add_argument(
    "--print",
    action="store_true",
    help="print flag to stdout rather than saving to file",
)
args = parser.parse_args()


def recv_until(sock, pattern):
    response = sock.recv(4096).decode()
    while len(response) < len(pattern) or response[-len(pattern) :] != pattern:
        response += sock.recv(4096).decode()
    return response

c = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
c.connect((args.host, args.port))

# Receive welcome, riddle, and prompt
response = recv_until(c, ":\r\n")

# Extract the encrypted riddle
split_response = response.split("\n")
riddle = split_response[1]

# Decrypt the riddle to get the key (we can use the plaintext,
# which we already know)
first_six_bytes = bytes.fromhex(riddle[:12])
plaintext = b"I'm ad"
key_bytes = bytes(a ^ b for a, b in zip(first_six_bytes, plaintext))
key = key_bytes.hex()
key_int = int(key, 16)

# Send the solution to the solver
c.sendall((str(key_int) + "\n").encode())

# Receive flag
flag = recv_until(c, "\r\n")

if args.print:
    print(f"flag: {flag}")
else:
    with open("flag", "w") as f:
        f.write(flag)
