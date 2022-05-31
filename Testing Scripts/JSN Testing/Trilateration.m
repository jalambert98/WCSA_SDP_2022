clc;
clear all;
close all;

r1 = readmatrix('C:\Users\Jack\Desktop\r1.txt');
r2 = readmatrix('C:\Users\Jack\Desktop\r2.txt');
r3 = readmatrix('C:\Users\Jack\Desktop\r3.txt');
flr = min([length(r1) length(r2) length(r3)]);

r1 = r1(1:flr);
r2 = r2(1:flr);
r3 = r3(1:flr);

% LPF on position data to smooth object tracking
bufSize = 16;
r1Buf = zeros(length(r1) + 1 - bufSize);
r2Buf = zeros(length(r2) + 1 - bufSize);
r3Buf = zeros(length(r3) + 1 - bufSize);
r1Sum = 0;
r2Sum = 0;
r3Sum = 0;

for i=1:length(r1)
    r1Sum = r1Sum + r1(i);
    r2Sum = r2Sum + r2(i);
    r3Sum = r3Sum + r3(i);
    
    if(i > bufSize)
        r1Sum = r1Sum - r1(i - bufSize);
        r2Sum = r2Sum - r2(i - bufSize);
        r3Sum = r3Sum - r3(i - bufSize);
    end
    
    if(i >= bufSize)
        r1Buf(i + 1 - bufSize) = r1Sum/bufSize;
        r2Buf(i + 1 - bufSize) = r2Sum/bufSize;
        r3Buf(i + 1 - bufSize) = r3Sum/bufSize;
    end
end

U = 60; % 60mm spacing between sensors
Vx = U*cosd(60);
Vy = U*sind(60);

x = (r1Buf.^2 - r2Buf.^2 + U^2) ./ (2*U);
y = (r1Buf.^2 - r3Buf.^2 + Vx^2 + Vy^2 - (2*Vx.*x)) ./ (2*Vy);
z = sqrt(r1Buf.^2 - x.^2 - y.^2);

% Recenter origin (-to center of triangle instead of corner sensor)
x = x - (U/2);
y = y - (Vy/2);

%    % Ignore imaginary/complex values
ind = x == real(x);
newX = x(ind(:,1),:);
newY = y(ind(:,1),:);
newZ = z(ind(:,1),:);

ind = y == real(y);
newX = newX(ind(:,1),:);
newY = newY(ind(:,1),:);
newZ = newZ(ind(:,1),:);

ind = z == real(z);
newX = newX(ind(:,1),:);
newY = newY(ind(:,1),:);
newZ = newZ(ind(:,1),:);

% Standardize axes limits
xlim_h = 500;
xlim_l = -xlim_h;
ylim_l = xlim_l;
ylim_h = xlim_h;
zlim_l = 0;
zlim_h = 2*xlim_h;


% Plot filtered xyz position of object over time
for i = 1:length(x)
    plot3(real(x(i)), real(y(i)), real(z(i)), 'o');
    
    xlim([xlim_l xlim_h]);
    ylim([ylim_l ylim_h]);
    zlim([zlim_l zlim_h]);
    set(gca,'xtick', xlim_l : (zlim_h/4) : xlim_h, 'xlim', [xlim_l, xlim_h])
    xline(x(i),'--r','x_c','LabelVerticalAlignment','bottom')
    set(gca,'ytick', ylim_l : (zlim_h/4) : ylim_h, 'ylim', [ylim_l, ylim_h])
    yline(y(i),'--r','y_c','LabelVerticalAlignment','bottom')
    %set(gca,'ztick', zlim_l : (zlim_h/4) : zlim_h, 'zlim', [zlim_l, zlim_h])
    %zline(z(i),'--r','z_c','LabelVerticalAlignment','bottom')

    grid on;
    xlabel('X');
    ylabel('Y');
    zlabel('Z');
    
    hold all
    
    drawnow
    pause(0.01)
    hold off;
end
