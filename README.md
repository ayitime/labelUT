# labelUT: Ultrasonic Phased Array Image Annotation Tool

**labelUT** is a versatile tool designed for annotating B-scan and C-scan images from ultrasonic phased array data. It allows users to label not only aligned targets but also the gate intervals in the C-scan image, which are typically represented in the B-scan. Additionally, it provides the functionality to label the corresponding C-scan slice locations in the B-scan image.

Inspired by the popular `labelImg` annotation tool, **labelUT** is built using C++ and Qt 5.12 for its core functionalities. While its primary use case focuses on ultrasonic phased array data, the tool can also be adapted for annotating other multi-modal datasets with orthogonal views.

Currently, **labelUT** supports the generation of labels in the YOLO format for object detection tasks.

![image](https://github.com/user-attachments/assets/ec80c309-1901-49b9-b7bc-8a2b35263e61)


## Features:
- Annotate B-scan and C-scan images simultaneously.
- Label aligned targets across B-scan and C-scan images.
- Annotate gate intervals in C-scan images as they correspond to B-scan.
- Supports multiple image formats such as PNG, JPG, JPEG, BMP, and TIFF.
- YOLO-style output for object detection annotations.

## Folder Structure:
To use **labelUT**, you need to organize your image files into the following directory structure. Taking B-scan and C-scan images as an example, the directory should look like this:
root/ 
├── B_scanImages/  label_B/ 
├── C_scanImages/  label_C/ 
└── label
      ├── B_scan
      ├── C_scan
      ├── classes.txt
      └── BC_info.json

Before starting the annotation process, you need to set the image folders for both modalities and the folder for storing the generated label files：

- **B_scanImages/** and **C_scanImages/**: These folders store the respective images. The images in both folders should have corresponding names and numbers, ensuring they match between the B-scan and C-scan folders (e.g., `1.png` in B-scan should correspond to `1.png` in C-scan).

- **label/**: This folder will store the annotation files. Before starting the annotation, you need to set the folder for saving the label files. Once set, two folders and files will be automatically generated: the **B_scan** and **C_scan** folders, which will contain the YOLO-format annotation files; **classes.txt**, which records all categories and their occurrence counts; and **BC_info.json**, which stores gate range information and intersection line data from the C-scan.

- Once the settings are correctly configured and there are no issues, the two lights on the left will turn green, indicating that you can begin the annotation process!

### Supported Image Formats:
- PNG
- JPG
- JPEG
- BMP
- TIFF

## Annotation Process:
Follow these steps to annotate your ultrasonic images with **labelUT**:

1. **Open Image Directories**:
   - Launch the software.
   - Click the `OpenDir` button on the left side of the interface.
   - In the pop-up windows, select the directories containing your B-scan and C-scan images. Ensure that both folders contain the same number of images.
   - If the image count matches, **labelUT** will successfully load the images and display them in the interface.

2. **Set Save Directories**:
   - Click the `Change Save Dir` button on the left side.
   - In the pop-up windows, specify the save directories for the B-scan and C-scan annotation files.
   
3. **Start Annotating**:
   - Once the directories are set, you can begin annotating the images in a manner similar to `labelImg`.
   - Use the interface to draw bounding boxes around the targets in both B-scan and C-scan images. The annotations will be saved in the respective label folders.
   - When dragging the bounding box, labelUT will detect the left and right boundaries of the boxes that are close in position between the two modalities, providing visual cues and a mouse snap effect.

## Installation:

To compile and run **labelUT**, ensure you have the following dependencies installed:

- Qt 5.12 or later
- C++ compiler

Clone the repository and follow the instructions in the `INSTALL.md` file for building the application.

```bash
git clone https://github.com/ayitime/labelUT.git
cd labelUT
# Follow the build instructions

