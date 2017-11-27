% This script generates the binary value of the PLSCODE for DVB-S2.

% The MODCOD field is 5 bits that indicate modulation and coding according 
% to table 12 in ETSI EN 302 307 V1.2.1. The TYPE field is two bits. MSB is 
% 0 = normal and 1 = short frame length. The LSB of the TYPE field is 
% 0 = no pilots and 1 = pilots. We use short frame length based on the 
% recommendation from CCSDS. This is also expected to alleviate latency. 

% G is the generator matrix given in DVB-S2. m is a concatenation of the 
% five bits of the MODCOD field and the MSB of the TYPE field. c is the 
% codeword produced by the multiplication of
% m and G. This result c is then expanded from 32 bits to 64, called d.
% There are two different possibilities for this step. If the LSB of the 
% TYPE field is 0, then there are no pilots, and each symbol of c is 
% repeated. If the LSB is the LSB of the TYPE field is 1, then each symbol 
% from c is repeated, but the second symbol is flipped. This result d is
% scrambled with PLSCODE_scramble (bitwise xor). This result is the
% PLSCODE_result. m, type_lsb, and PLSCODE_result are all written out to a 
% file called plscode.mat


G = [0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1;
     0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1;
     0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1;
     0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1;
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1;
     1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1];

 
m = [0 0 1 0 0 1]

c = mod(double(m)*double(G),2); %binary matrix multiplication assuming xor



type_lsb = 1
d = zeros([1 64]); %create repeated element codeword array
d_odd = c; %get the odd elements for d. It's elements of c.
d_even = xor(1,c); %get the even elements for d. It's c flipped.

if type_lsb == 0
    d = repelem(c,2); %if TYPE lsb is 0, just repeat each element of c twice and put it in d
else
    for i = 1:32        
        d(2*i) = d_even(i);
        d(2*i-1) = d_odd(i);
    end
end

%disp(d)

PLSCODE_scramble = [0 1 1 1 0 0 0 1 1 0 0 1 1 1 0 1 1 0 0 0 0 0 1 1 1 1 0 0 1 0 0 1 0 1 0 1 0 0 1 1 0 1 0 0 0 0 1 0 0 0 1 0 1 1 0 1 1 1 1 1 1 0 1 0 ];

PLSCODE_result = xor(d, PLSCODE_scramble)

save("all_values_from_plscode.mat", 'm', 'type_lsb' , 'PLSCODE_result')

save("plscode.mat", 'PLSCODE_result')


type('plscode.mat')


%c(3) = xor(c(3), 0)  %introduce an error. Or three. Along the way.

H = G' % create parity check matrix by transpose binary matrix G
test_result = mod(double(c)*double(H),2)

%if the test_result is all zeros, then c is a codeword. 

%load handel
%sound(y,Fs)