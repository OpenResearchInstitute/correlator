%imports the output of PLSCODE.m, which generates a binary representation
%of the PLSCODE for DVB-S2, and produces the transmitted symbols of the
%physical layer header, according to DVB-S2.

%a = uint8([1;2;3;4]);
%b = uint8([2;2;7;7]);

%z = complex(a,b)
%z = 4x1 uint8 column vector
% 1 + 2i
% 2 + 2i
% 3 + 7i
% 4 + 7i

%PLSCODE = [1 1 0 1 1 0 1 1 1 1 0 0 1 0 0 0 0 0 1 0 1 0 0 1 1 0 0 1 1 1 0 0 1 1 1 1 1 0 0 1 0 0 0 1 0 1 1 1 1 0 0 0 0 1 1 1 1 0 1 0 1 1 1 1]
%uncomment the above if you can't run PLSCODE.m

PLSCODE = importdata('plscode.mat')

%SOF is 18D2E82 HEX which is is 0 1 1 0 0 0 1 1 0 1 0 0 1 0 1 1 1 0 1 0 0 0 0 0 1 0
SOF = [0 1 1 0 0 0 1 1 0 1 0 0 1 0 1 1 1 0 1 0 0 0 0 0 1 0];

PLHEADER = horzcat(SOF,PLSCODE);

%The PLHEADER, represented by the binary sequence (y1, y2,...y90) shall be modulated into 90 π/2BPSK symbols according to the rule: 
% I of 2i-1 = Q of 2i-1 = (1/√2) (1-2*y of 2i-1), I of 2i = - Q of 2i = - (1/√2) (1-2*y of 2i) for i = 1, 2, ..., 45 

%imaginary Q vertical, real I horizontal

Imaginary = zeros([1,90]);
Reals = zeros([1,90]);

for i = 1:45
    Imaginary((2*i)-1) = (1/sqrt(2))*(1-2*PLHEADER((2*i)-1));
    Reals((2*i)-1) = (1/sqrt(2))*(1-2*PLHEADER((2*i)-1));
    Imaginary(2*i) = -(1/sqrt(2))*(1-2*PLHEADER(2*i));
    Reals(2*i) = -(1/sqrt(2))*(1-2*PLHEADER(2*i));
end

%this is a column vector of complex numbers that are the encoded symbols
%for the PLHEADER in pi/2 BPSK modulation. 

TX_PLHEADER = complex(Reals, Imaginary)

save("tx_plheader.mat", 'TX_PLHEADER')

