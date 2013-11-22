def bytes_from_file(filename, chunksize=8192):
    with open(filename, "rb") as f:
        while True:
            chunk = f.read(chunksize)
            if chunk:
                for b in chunk:
                    yield b
            else:
                break
count = 0
out = open("doom1wad.c", "w")
print >>out, "const char doom1waddata[] = {"
for b in bytes_from_file('doom1.wad'):
    print >>out, "0x%02x, "%(ord(b)),
    count = count + 1
    if (count % 16) == 0:
        print >>out
print >>out, "};"
print >>out, "const unsigned doom1waddatasize = ", count, ";"
