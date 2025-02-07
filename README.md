labelUT: Ultrasonic Phased Array Image Annotation Tool
labelUT is a versatile tool designed for annotating B-scan and C-scan images from ultrasonic phased array data. It allows users to label not only aligned targets but also the gate intervals in the C-scan image, which are typically represented in the B-scan. Additionally, it provides the functionality to label the corresponding C-scan slice locations in the B-scan image.

Inspired by the popular labelImg annotation tool, labelUT is built using C++ and Qt 5.12 for its core functionalities. While its primary use case focuses on ultrasonic phased array data, the tool can also be adapted for annotating other multi-modal datasets with orthogonal views.

Currently, labelUT supports the generation of labels in the YOLO format for object detection tasks.

Features:
Annotate B-scan and C-scan images simultaneously.
Label aligned targets across B-scan and C-scan images.
Annotate gate intervals in C-scan images as they correspond to B-scan.
Supports multiple image formats such as PNG, JPG, JPEG, BMP, and TIFF.
YOLO-style output for object detection annotations.
Folder Structure:
To use labelUT, you need to organize your image files into the following directory structure. Taking B-scan and C-scan images as an example, the directory should look like this:

markdown
复制
编辑
root/
    ├── label_B/
    ├── label_C/
    ├── B_scan/
    └── C_scan/
B_scan/ and C_scan/: Store the respective images. These folders should contain the same number of images, which will be paired for annotation. The naming convention should be as similar as possible between B-scan and C-scan images, with only the suffix differing (e.g., 1_B.png, 1_C.png, 2_B.png, 2_C.png).

label_B/ and label_C/: These folders will store the annotation files for the B-scan and C-scan images, respectively. Annotations will be saved in YOLO format.

Supported Image Formats:
PNG
JPG
JPEG
BMP
TIFF
Annotation Process:
Follow these steps to annotate your ultrasonic images with labelUT:

Open Image Directories:

Launch the software.
Click the OpenDir button on the left side of the interface.
In the pop-up windows, select the directories containing your B-scan and C-scan images. Ensure that both folders contain the same number of images.
If the image count matches, labelUT will successfully load the images and display them in the interface.
Set Save Directories:

Click the Change Save Dir button on the left side.
In the pop-up windows, specify the save directories for the B-scan and C-scan annotation files.
Start Annotating:

Once the directories are set, you can begin annotating the images in a manner similar to labelImg.
Use the interface to draw bounding boxes around the targets in both B-scan and C-scan images. The annotations will be saved in the respective label folders.
Installation:
To compile and run labelUT, ensure you have the following dependencies installed:

Qt 5.12 or later
C++ compiler
Clone the repository and follow the instructions in the INSTALL.md file for building the application.

bash
复制
编辑
git clone https://github.com/yourusername/labelUT.git
cd labelUT
# Follow the build instructions
Contribution:
We welcome contributions to enhance labelUT. If you encounter any issues or wish to propose a new feature, please open an issue or submit a pull request.
