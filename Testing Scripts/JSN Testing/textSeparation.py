"""
File:   textSeparation.py

Originally written by Cody Lambert
Further modified by Jack Lambert
"""

my_dict = {'r1': [], 'r2': [], 'r3': []}

def file_manipulation(file):
    print("opening  \"" + file + "\"...")

    # first get all lines from file
    with open(file, 'r') as f:
        lines = f.readlines()

    print("removing spaces...")

    # remove spaces
    lines = [line.replace(' ', '') for line in lines]
    lines = [line.replace('\0', '') for line in lines]

    print("modifying original file...")
    # finally, write lines in the file
    with open(file, 'w') as f:
        f.writelines(lines)

    for line in lines:
        if "S1=" in line:
            justNum = line.replace("S1=", "")
            my_dict['r1'].append(justNum)
        elif "S2=" in line:
            justNum = line.replace("S2=", "")
            my_dict['r2'].append(justNum)
        elif "S3=" in line:
            justNum = line.replace("S3=", "")
            my_dict['r3'].append(justNum)
            


def populate_file(r1, r2, r3):
    fh1 = open(r1, 'a')
    fh1.truncate(0)
    fh2 = open(r2, 'a')
    fh2.truncate(0)
    fh3 = open(r3, 'a')
    fh3.truncate(0)

    for item in my_dict['r1']:
        fh1.write(str(item))
    fh1.close()
    for item in my_dict['r2']:
        fh2.write(str(item))
    fh2.close()
    for item in my_dict['r3']:
        fh3.write(str(item))
    fh3.close()


def main():
    file_manipulation('sensReadings.txt')
    populate_file('r1.txt', 'r2.txt', 'r3.txt')


if(__name__ == "__main__"):
    main()