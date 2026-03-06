# labelUT: Phased Array Ultrasonic Orthogonal View Image Annotation Tool

**labelUT** is a versatile tool designed for annotating B-scan and C-scan images from ultrasonic phased array data. It allows users to label not only aligned targets but also the gate intervals in the C-scan image, which are typically represented in the B-scan. Additionally, it provides the functionality to label the corresponding C-scan slice locations in the B-scan image.

Inspired by the popular `labelImg` annotation tool, **labelUT** is built using C++ and Qt 5.12 for its core functionalities. While its primary use case focuses on ultrasonic phased array data, the tool can also be adapted for annotating other multi-modal datasets with orthogonal views.

Currently, **labelUT** supports the generation of labels in the YOLO format for object detection tasks.

<div align=center>
<img src="https://github.com/user-attachments/assets/ec80c309-1901-49b9-b7bc-8a2b35263e61" width="500">
</div>

## Features:
- Annotate B-scan and C-scan images simultaneously. 
- Label aligned targets across B-scan and C-scan images.
- Annotate gate intervals in C-scan images as they correspond to B-scan.
- Supports multiple image formats such as PNG, JPG, JPEG, BMP, and TIFF.
- YOLO-style output for object detection annotations.

## Folder Structure:
To use **labelUT**, you need to organize your image files into the following directory structure. Taking B-scan and C-scan images as an example, the directory should look like this:

    root/
    ├── B_scanImages/ 
    |      ├── 1.png
    |      └── 2.png 
    ├── C_scanImages/
    |      ├── 1.png
    |      └── 2.png
    |
    └── label/
          ├── B_scan/
          |   ├── 1.txt
          |   └── 2.txt
          ├── C_scan/
          |   ├── 1.txt
          |   └── 2.txt
          |
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
   
<div align=center>
<img src="https://github.com/user-attachments/assets/caaf49cc-a394-495e-b7dd-d1617f399491" width="500">
</div>

2. **Set Label Save Directories**:
   - Click the `Change Save Dir` button on the left side.
   - In the pop-up windows, specify the save directories for the B-scan and C-scan annotation files.

<div align=center>
<img src="https://github.com/user-attachments/assets/6a24bc95-c0d5-49ea-b870-4d6c99cc8c1f" width="500">
</div>
   
3. **Start Annotating**:
   - Once the directories are set, you can begin annotating the images in a manner similar to `labelImg`.
   - Use the interface to draw bounding boxes around the targets in both B-scan and C-scan images. The annotations will be saved in the respective label folders.
   - When dragging the bounding box, labelUT will detect the left and right boundaries of the boxes that are close in position between the two modalities, providing visual cues and a mouse snap effect.

<div align=center>
<img src="https://github.com/user-attachments/assets/4be0b94b-14ed-4098-8372-590c7e098e82" width="500">
</div>

<div align=center>
<img src="https://github.com/user-attachments/assets/298fbbb9-2772-438a-9030-a13918ed6e1b" width="500">
</div>

4. **Keyboard Shortcuts**:
   - `W`: Draw a bounding box.
   - `A`: Switch to the previous pair of B-scan and C-scan images.
   - `D`: Switch to the next pair of images.
   - `Ctrl + S`: Save current annotations.
   - `Delete`: Delete the selected bounding box.


## Installation:

To compile and run **labelUT**, ensure you have the following dependencies installed:

- Qt 5.12 or later
- C++ compiler

Clone the repository and follow the instructions in the `INSTALL.md` file for building the application.

```bash
git clone https://github.com/ayitime/labelUT.git
cd labelUT
# Follow the build instructions
```

## Source Code Availability:
~~The source code will be made publicly available as soon as possible. Please stay tuned.~~  
The source code has now been released in the `labelUTsourceCode` directory ♪(´▽｀).

## 📖 Citation

😄 If you find this work useful for your research, please cite:

```bibtex
@article{na2026ovanet,
  title={A deep mutual learning-based framework for wind turbine blade defect detection in multimodal phased array ultrasonic data},
  author={Na, Yiming and He, Yunze and Deng, Baoyuan and Yang, Chunlei and Li, Qiying and Wang, Liwen and Cao, Yi},
  journal={Ultrasonics},
  volume={164},
  pages={108035},
  year={2026},
  issn={0041-624X},
  doi={10.1016/j.ultras.2026.108035}
}
 
