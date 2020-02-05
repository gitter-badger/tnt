import numpy as np

'''
    Credits go to
    https://pvigier.github.io/2018/06/13/perlin-noise-np.html
'''

'''
    TODO:
    translate this to Lua/C++.
'''


def func(t): return 6*t**5-15*t**4+10*t**3


def generate_perlin_noise_2d(shape, res):
    delta = (res[0]/shape[0], res[1]/shape[1])
    d = (shape[0]//res[0], shape[1]//res[1])
    grid = np.mgrid[0:res[0]:delta[0],
                    0:res[1]:delta[1]].transpose(1, 2, 0) % 1
    # Gradients
    angles = 2*np.pi*np.random.rand(res[0]+1, res[1]+1)
    gradients = np.dstack((np.cos(angles), np.sin(angles)))
    g00 = gradients[0:-1, 0:-1].repeat(d[0], 0).repeat(d[1], 1)
    g10 = gradients[1:, 0:-1].repeat(d[0], 0).repeat(d[1], 1)
    g01 = gradients[0:-1, 1:].repeat(d[0], 0).repeat(d[1], 1)
    g11 = gradients[1:, 1:].repeat(d[0], 0).repeat(d[1], 1)
    # Ramps
    n00 = np.sum(grid*g00, 2)
    n10 = np.sum(np.dstack((grid[:, :, 0]-1, grid[:, :, 1]))*g10, 2)
    n01 = np.sum(np.dstack((grid[:, :, 0], grid[:, :, 1]-1))*g01, 2)
    n11 = np.sum(np.dstack((grid[:, :, 0]-1, grid[:, :, 1]-1))*g11, 2)
    # Interpolation
    t = func(grid)
    n0 = n00*(1-t[:, :, 0])+t[:, :, 0]*n10
    n1 = n01*(1-t[:, :, 0])+t[:, :, 0]*n11
    return np.sqrt(2)*((1-t[:, :, 1])*n0+t[:, :, 1]*n1)


def generate_fractal_noise_2d(shape, res, octaves=1, persistence=0.5):
    noise = np.zeros(shape)
    freq = 1
    ampl = 1
    for _ in range(octaves):
        noise += ampl * \
            generate_perlin_noise_2d(shape, (freq*res[0], freq*res[1]))
        freq *= 2
        ampl *= persistence
    return noise


def write_to_file(file, result):
    return


if __name__ == "__main__":
    ret = generate_fractal_noise_2d(100, 10)
    pass
