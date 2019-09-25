import os
import hashlib
import re

MARGIN = 100 - 40 - 8 + 7 - 1

counter = 0

def mkhash(dat):
    global counter
    # conc = ""
    for i in dat:
        # conc += re.sub('\s*', '', i) + "\n"
        counter += 1;
        hash = str(hex(counter))[2:]
        while len(hash) < 3:
            hash = "0" + hash
        yield hash
        # yield hashlib.md5(conc).hexdigest()[:2]

for path, dirs, files in os.walk('./code'):
    for f in files:
        if (f.endswith(".cpp") or f.endswith('.java') or f.endswith('.sh')) and not f.endswith(".test.cpp"):
            p = os.path.join(path, f)
            q = os.path.join("_code", '/'.join(path.split('\\')[1:]), f)
            print(q)

            try:
                os.makedirs(os.path.dirname(q))
            except:
                pass

            dat = [ line for line in open(p).read().splitlines() if not line.startswith('// vim: ') and not line.startswith('# vim: ') ]
            with open(q, 'w') as out:
                warning = False
                error = False
                last = False
                for dat, hash in zip(dat, mkhash(dat)):
                    last = False
                    s = dat.lstrip(' ')
                    add = len(dat) - len(s)
                    if add > 0:
                        s = ' ' + s
                        add -= 1
                    s = '-'*add + s
                    if(len(s) > MARGIN):
                        print(s, file=out)
                        warning = True
                        last = True
                        if len(s) > MARGIN+4:
                            error = True
                            print(len(s), MARGIN)
                            print(repr(s))
                    else:
                        if len(s) < MARGIN:
                            s = s+' '
                        print(s.ljust(MARGIN, '-') + "//" + hash, file=out)

            if last:
                error = True
            if error:
                print('ERROR: Code too wide: %s' % p)
            elif warning:
                print('WARNING: Code (almost) too wide: %s' % p)
