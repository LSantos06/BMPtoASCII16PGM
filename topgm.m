img = imread('KinectScreenshot-Depth-03-37-20.bmp');
img1 = rgb2gray(img);
img1ui16 = im2uint16(img1);

[height, width] = size(img1ui16);

fileID = fopen('KinectScreenshot-Depth-03-37-20.pgm', 'w');

fprintf(fileID, "P2\n");
fprintf(fileID, width + " " + height + "\n");
fprintf(fileID, "65535\n");

for i=1:height
    for j=1:width
        number = img1ui16(i,j);
        number_acii = num2str(number);
        fprintf(fileID, number_acii + " ");
    end
    fprintf(fileID, "\n");
end

fclose(fileID);