clc;
clear all;
close all;

r1 = readmatrix('C:\Users\Jack\Desktop\sensReadings.txt');
r1 = transpose(r1);
deltaT = 50e-3;
t = 0:deltaT:(deltaT*length(r1) - deltaT);

plot(t, r1)
title('Single Sensor: Small Round Object (Medium)');
xlabel('Time [seconds]');
ylabel('Distance [millimeters]');