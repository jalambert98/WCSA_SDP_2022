clc;
clear all;
close all;

JSN_dist = readmatrix('C:\Users\student\Desktop\JSN_readings.txt');
Lidar_dist = readmatrix('C:\Users\student\Desktop\Lidar_readings.txt');

Lidar_dT = 10e-3;
JSN_dT = 50e-3;

JSN_t = 0:JSN_dT:(JSN_dT*(length(JSN_dist) - 1));
Lidar_t = 0:Lidar_dT:(Lidar_dT*(length(Lidar_dist) - 1));

figure(1)
subplot(211)
plot(JSN_t, JSN_dist)
title('Ultrasonic Sensor (JSN-SR04T)')
xlabel('Time [s]')
ylabel('Distance [mm]')
ylim([0 7500]);

subplot(212)
plot(Lidar_t, Lidar_dist)
title('LiDAR Sensor (TF MiniPlus)')
xlabel('Time [s]')
ylabel('Distance [mm]')
ylim([0 7500]);

