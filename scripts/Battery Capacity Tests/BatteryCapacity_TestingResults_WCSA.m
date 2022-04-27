close all;
clear all;
clc;

%%
data120 = readmatrix("C:\Users\student\Desktop\LiPo_DischargeFromFull_120mA.csv");
data120 = data120(6:(length(data120)-8), 1:3);

sec120 = data120(1:length(data120), 1) - data120(1, 1);
min120 = sec120./60;

Vbat120bw = data120(1:length(data120), 2);
Vr1120bw = data120(1:length(data120), 3);
for i=1:length(sec120)
    Vbat120(i) = Vbat120bw(length(sec120) - i + 1);
    Vr1120(i) = Vr1120bw(length(sec120) - i + 1);
    RL120(i) = Vbat120(i)/Vr1120(i);
end

figure(1)
subplot(311)
plot(min120, Vbat120)
title('V_B_A_T vs. Time  -  [R_L_m_e_a_s = 43.7\Omega], [I_L ~ 120mA]');
xlabel('Time [min]');
ylabel("V_B_A_T [V]");
subplot(312)
plot(min120, Vr1120)
title('V_R_1 [for I_L] vs. Time  (R_1 is 1\Omega series resistor from Bat Terminals)');
xlabel('Time [min]');
ylabel("V_R_1 [V] --> I_L [A]");
subplot(313)
plot(min120, RL120)
title('(V_B_A_T/I_L) = R_L vs. Time');
xlabel('Time [min]');
ylabel("(V_B_A_T/I_L) = R_L [\Omega]");


data350 = readmatrix("C:\Users\student\Desktop\LiPo_DischargeFromFull_350mA.csv");
sec350 = data350(1:length(data350), 1);
min350 = sec350./60;

Vbat350bw = data350(1:length(data350), 2);
for i=1:length(sec350)
    Vbat350(i) = Vbat350bw(length(sec350) - i + 1);
end

figure(2)
plot(min350, Vbat350)
title('V_B_A_T vs Time  -  [R_L = 11.4\Omega], [I_L ~ 350mA]');

