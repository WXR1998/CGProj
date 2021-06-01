import matplotlib.pyplot as plt
import numpy as np

in_path = './data/1.in'
out_path = './data/1.out'
coor_range = 20000
alpha = 0.3

if __name__ == '__main__':
    with open(in_path, 'r') as fin:
        n = int(fin.readline())
        p = np.array([[int(coor) for coor in line.split()] for line in fin.readlines()], dtype=int)

    plt.figure(figsize=(10, 10))
    plt.xlim((-coor_range, coor_range))
    plt.ylim((-coor_range, coor_range))
    plt.scatter(p[:, 0], p[:, 1], s=3, alpha=0.6)

    with open(out_path, 'r') as fin:
        try:
            type, width = fin.readline().strip().split()
        except:
            print('[Error] In reading input file.')
            exit(0)
        if type == 'NORMAL':
            inner = fin.readline().strip()
            outer = fin.readline().strip()
            inner = [_[1:-1].split(', ') for _ in inner[inner.find(' ')+1:].split(' - ')]
            inner = [[int(_[0]), int(_[1])] for _ in inner]
            outer = [_[1:-1].split(', ') for _ in outer[outer.find(' ')+1:].split(' - ')]
            outer = [[int(_[0]), int(_[1])] for _ in outer]
            plt.plot(   [inner[0][0], inner[1][0], inner[1][0], inner[0][0], inner[0][0]], 
                        [inner[0][1], inner[0][1], inner[1][1], inner[1][1], inner[0][1]], 
                        c='red', alpha=alpha)
            plt.plot(   [outer[0][0], outer[1][0], outer[1][0], outer[0][0], outer[0][0]], 
                        [outer[0][1], outer[0][1], outer[1][1], outer[1][1], outer[0][1]], 
                        c='green', alpha=alpha)
            
        elif type == 'STRIPE_HORIZONTAL':
            y1 = int(fin.readline())
            y2 = int(fin.readline())
            plt.axhline(y1, c='red', alpha=alpha)
            plt.axhline(y2, c='red', alpha=alpha)
        elif type == 'STRIPE_VERTICAL':
            x1 = int(fin.readline())
            x2 = int(fin.readline())
            plt.axvline(x1, c='red', alpha=alpha)
            plt.axvline(x2, c='red', alpha=alpha)
        elif type == 'L_SHAPED':
            ax, ay = [int(_) for _ in fin.readline().strip()[1:-1].split(', ')]
            bx, by = [int(_) for _ in fin.readline().strip()[1:-1].split(', ')]
            if ay <= by:
                plt.plot([ax, ax], [ay, coor_range], c='red', alpha=alpha)
                plt.plot([bx, bx], [by, coor_range], c='red', alpha=alpha)
            else:
                plt.plot([ax, ax], [-coor_range, ay], c='red', alpha=alpha)
                plt.plot([bx, bx], [-coor_range, by], c='red', alpha=alpha)
            if ax <= bx:
                plt.plot([ax, coor_range], [ay, ay], c='red', alpha=alpha)
                plt.plot([bx, coor_range], [by, by], c='red', alpha=alpha)
            else:
                plt.plot([-coor_range, ax], [ay, ay], c='red', alpha=alpha)
                plt.plot([-coor_range, ay], [by, by], c='red', alpha=alpha)

        else:
            asc = [_.split(', ') for _ in fin.readline().strip().split(') (')[1:-1]]
            asc = np.array([[int(_[0]), int(_[1])] for _ in asc])
            des = [_.split(', ') for _ in fin.readline().strip().split(') (')[1:-1]]
            des = np.array([[int(_[0]), int(_[1])] for _ in des])
            hor = [_.split(', ') for _ in fin.readline().strip().split(') (')[1:-1]]
            hor = np.array([[int(_[0]), int(_[1])] for _ in hor])
            can = [_.split(', ') for _ in fin.readline().strip().split(') (')[1:-1]]
            can = np.array([[int(_[0]), int(_[1])] for _ in can])
            plt.plot(asc[:, 0], asc[:, 1], c='red', alpha=alpha)
            plt.plot(des[:, 0], des[:, 1], c='green', alpha=alpha)
            plt.plot(hor[:, 0], hor[:, 1], c='cyan', alpha=alpha)
            plt.scatter(can[:, 0], can[:, 1], s=10, c='black', alpha=alpha)

    plt.title(f'Distribution of the points in [{in_path}]\nwidth = {width}')
    plt.tight_layout()

    plt.show()
