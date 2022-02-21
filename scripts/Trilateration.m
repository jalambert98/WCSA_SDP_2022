clc;
close all;

r1 = readmatrix('r1.txt');
r2 = readmatrix('r2.txt');
r3 = readmatrix('r3.txt');
flr = min([length(r1) length(r2) length(r3)]);

r1 = r1(1:flr);
r2 = r2(1:flr);
r3 = r3(1:flr);

U = 60; % 60mm spacing between sensors
Vx = U*cosd(60);
Vy = U*sind(60);

x = real((r1.^2 - r2.^2 + U^2) ./ (2*U));
y = real((r1.^2 - r3.^2 + Vx^2 + Vy^2 - (2*Vx.*x)) ./ (2*Vy));
z = sqrt(r1.^2 - x.^2 - y.^2);

x = x - (U/2);
y = y - (Vy/2);

[real(x) real(y) real(z)]

xlim_h = 500;
xlim_l = -xlim_h;

ylim_l = xlim_l;
ylim_h = xlim_h;
zlim_l = 0;
zlim_h = 2*xlim_h;

for i = 1:length(x)
    plot3(real(x(i)), real(y(i)), real(z(i)), 'o');
    
    xlim([xlim_l xlim_h]);
    ylim([ylim_l ylim_h]);
    zlim([zlim_l zlim_h]);
    
    grid on;
    xlabel('X');
    ylabel('Y');
    zlabel('Z');
    hold all
    
    drawnow
    pause(0.065)
    hold off;
end
