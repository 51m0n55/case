import os

bnames = ''
snames = ''
#casenames = ''
skincount = 0


while True:
    
    inp = input(":")

    if inp == '':
        print(bnames)
        print(snames)
        #print(casenames)
        print(f'skincount = {skincount}')
        skincount = 0
        bnames = ''
        snames = ''

    else:
        skincount += 1
        doing = 0
        sted = ['','']
        normname = ''
        for ch in inp:
            if ch == "|":
                doing = 1
                sted[0] = sted[0][:-1]
                sted[0] += "_"
            else:
                if ch not in ["-"," "]:
                    sted[doing] += ch.upper()
                else:
                    sted[doing] += '_'
                if doing == 1:
                    normname += ch
        sted[1] = sted[1][1:]
        normname = normname[1:]
        os.system('cls')
        name = ' '+sted[0]+sted[1]+','
        bnames += name
        #print(sted[1])
        snames += f'{{{sted[0][:-1]}, "{normname}", change}}, '
        if skincount%4==0:
            snames += '\n'
        #casenames += f'skinlist[{sted[0]+sted[1]}],\n'
