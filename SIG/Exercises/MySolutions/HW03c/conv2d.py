import os

import numpy as np
from PIL import Image, ImageOps

kernels = {
    'sharpness': np.array([[0, -1, 0], [-1, 5, -1], [0, -1, 0]]),
    'horizontal_edge': np.array([[-1, -1, -1], [0, 0, 0], [1, 1, 1]]),
    'embossing': np.array([[2, 0, 0], [0, -1, 0], [0, 0, -1]]),
    'gaussian': np.array([
        [1, 4, 7, 4, 1],
        [4, 16, 26, 16, 4],
        [7, 26, 41, 26, 7],
        [4, 16, 26, 16, 4],
        [1, 4, 7, 4, 1],
    ]) * (1 / 273),
}

strides = {
    'sharpness': 1,
    'horizontal_edge': 2,
    'embossing': 3,
    'gaussian': 1,
}

is_same = {
    'sharpness': False,
    'horizontal_edge': True,
    'embossing': False,
    'gaussian': True,
}

kernel_names = list(kernels.keys())

def conv2d(src, out, stride = 2, is_same = True, kernel = kernels['sharpness']):
    image_object = Image.open(src)
    image_object = ImageOps.grayscale(image_object)
    image_array = np.asarray(image_object)

    n = image_array.shape[0]
    f = kernel.shape[0]
    p = ((f - 1) // 2) if is_same else 0
    output_size = ((n + (2*p) - f) // stride) + 1
    
    image_array = np.pad(image_array, p, constant_values=0)
    
    output_array = np.zeros(shape=(output_size, output_size))


    for i in range(output_size):
        for j in range(output_size):
            convolved_part = image_array[i * stride: (i * stride) + f, j * stride: (j * stride) + f]
            conv_result = np.sum(convolved_part * kernel)
            output_array[i,j] = max(0, min(255, conv_result))
    
    output_array = np.uint8(output_array)

    output_image_object = Image.fromarray(output_array)
    output_image_object.save(out)

def main():
    input_dir = 'input_images'
    output_dir = 'output_images'

    input_files = list(filter(lambda x: not (os.path.isfile(x) and x.lower().endswith('.jpg')), os.listdir(input_dir)))

    for kernel_name in kernel_names:
        for input_file in input_files:
            input_file_basename = ''.join(input_file.split('.')[:-1])
            output_filename = f'{input_file_basename}_{kernel_name}_{"same" if is_same[kernel_name] else "valid"}_{strides[kernel_name]}.jpg'
            
            input_src = os.path.join(input_dir, input_file)
            output_src = os.path.join(output_dir, output_filename)

            print(f' ==> Processing {output_filename}... ', end = '', flush=True)

            conv2d(input_src, output_src, strides[kernel_name], is_same[kernel_name], kernels[kernel_name])

            print('Done.')

if __name__ == '__main__':
    main()