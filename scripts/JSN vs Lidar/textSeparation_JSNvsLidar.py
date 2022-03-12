"""
File:   textSeparation_JSNvsLidar.py

Originally written by Cody Lambert
Further modified by Jack Lambert
"""

my_dict = {'JSN': [], 'Lidar': []}

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
        if "J" in line:
            justNum = line.replace("J", "")
            my_dict['JSN'].append(justNum)
        elif "L" in line:
            justNum = line.replace("L", "")
            my_dict['Lidar'].append(justNum)
            


def populate_file(JSN, Lidar):
    print("populating new files...")
    fh1 = open(JSN, 'a')
    fh1.truncate(0)
    fh2 = open(Lidar, 'a')
    fh2.truncate(0)

    for item in my_dict['JSN']:
        fh1.write(str(item))
    fh1.close()
    for item in my_dict['Lidar']:
        fh2.write(str(item))
    fh2.close()

    print("DONE!")


def main():
    file_manipulation('sensReadings.txt')
    populate_file('JSN_readings.txt', 'Lidar_readings.txt')


if(__name__ == "__main__"):
    main()