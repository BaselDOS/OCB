close all;
figure(1)
plot(length_vs_runtime(:,2),length_vs_runtime(:,1));
hold on;
plot(length_vs_runtime(:,3),length_vs_runtime(:,1));
title("Run time in clock cycles vs Input length in bytes");
subtitle("without dynamic memory");
xlabel("Run time [Clock Cycles]");
ylabel("Input length [Bytes]");
legend("without accerelator","with accerelator");
grid on;
figure(2)
title("Run time in clock cycles vs Input length in bytes");
plot(length_vs_runtime(:,4),length_vs_runtime(:,1));
hold on;
plot(length_vs_runtime(:,5),length_vs_runtime(:,1));
title("Run time in clock cycles vs Input length in bytes");
subtitle("with dynamic memory");
xlabel("Run time [Clock Cycles]");
ylabel("Input length [Bytes]");
legend("without accerelator","with accerelator");
grid on;


