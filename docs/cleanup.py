import sys, cleanuphelp

args = sys.argv[1:]
assert len(args) > 0, "Please speficy a file"

f1 = args[0]
f2 = args[1]

r = open(f1, mode="r")
outHTML = cleanuphelp.parseContent(r.read())
r.close()

print("Cleaning up:\n" + f1 + "\n Into HTML:\n" + f2)

out = open(f2, mode="w")
out.write(outHTML)
out.close()
