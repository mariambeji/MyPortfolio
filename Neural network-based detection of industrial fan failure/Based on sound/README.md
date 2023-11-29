## Presentation

The work consists in training a sound classification model to detect the state of a fan in an industrial environment.
The dataset used can be found through this link :
https://zenodo.org/record/3384388#.YTi1Tk4YBPZ
It is arranged as follows:

![image](https://user-images.githubusercontent.com/108965218/234117820-e66dde30-f504-4d6a-a961-2d80b83de905.png)

The layout was then modified as follows:

![image](https://user-images.githubusercontent.com/108965218/234117886-0e6d334e-26be-4584-a7b8-a3084f696052.png)

The model behaves like an image classifier: the input nodes are fed by a matrix named Log-Mel spectrogram.
In short, the log-mel spectrogram is like a set of FFTs put end to end while applying a scale modification to get closer to the behavior of the human ear.

![image](https://user-images.githubusercontent.com/108965218/234117969-1e8c54a6-81e2-486f-9e84-49222de3bb88.png)

The parameters of the spectrogram and the structure of the model have been adapted to the limitation imposed by the microcontroller(especially the size of the RAM limited to 96 KB).
The preprocessing consists in preparing a csv file containing the metadata. Moreover, it is a question of normalizing all the files present (same duration, same sampling frequency as well as a mono format) so that the spectrograms obtained are of the same dimension (in our case 30*32) as shown in the following figure:

![image](https://user-images.githubusercontent.com/108965218/234118118-cf8cea2a-9606-47b9-8e22-cf810cb6b81d.png)

Once the model was trained, it was exported in ".pth" file. As this file is not directly compatible with the current version of the STM32 Cube AI suite, I had to convert it to a more generic format ONNX (Open Neural Network Exchange).
The program implemented on microcontroller follows the following flowchart:

![image](https://user-images.githubusercontent.com/108965218/234118170-ded4a860-bd31-4b9f-a7bf-9306b499576a.png)

