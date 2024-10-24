clear
clc

fname = 'build/output.csv';
if exist(fname, 'file') ~= 2
    fprintf(1,'File Not Found!!!\n');
    return
end

data = readmatrix(fname);

figure(1)
plot(data(:,1), data(:,2),'b')
xlabel('time   (sec)')
ylabel('Signal values')
title('Plot of Time-Domain Signal')

    

    