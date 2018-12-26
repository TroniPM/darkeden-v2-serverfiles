# darkeden-v2-serverfiles
Endless work...

Compress "src/" folder as "vs.tar.xz", remove "src/" folder, create a docker image, and run the image as follows bellow (IMPORTANT: in THAT order.):

```sh
sudo docker build -t YOUR_NAME_HERE .
sudo docker run -it YOUR_NAME_HERE
```

Copy "src/" folder to container (runtime) ```sudo docker cp src/ CONTAINERID:/home/darkeden```.