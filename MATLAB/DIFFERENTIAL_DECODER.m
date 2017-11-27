%this script is the differential decoder from the DVB-S2 implementation
%guidelines. The pi/2 BPSK encoded physical layer header is decoded. The
%output of the script DIFFERENTIAL_ENCODER is imported, and a differential
%decoding is peformed. A complex result is saved. 

RX_PLHEADER = importdata('tx_plheader.mat');

disp(RX_PLHEADER);
DECODED_PLHEADER = complex(zeros([1,90]), zeros([1,90]));



for i = 1:89
    DECODED_PLHEADER(i) = RX_PLHEADER(i+1) * conj(RX_PLHEADER(i))
end

save("decoded_plheader.mat", 'DECODED_PLHEADER')
