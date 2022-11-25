clear

clock_channel=8;
SNSPD_channel_1H=1;
SNSPD_channel_1V=3;
SNSPD_channel_2H=2;
SNSPD_channel_2V=4;
channel = [1,3,2,4,5];


% tagger = TimeTagger;
% stream = TTTimeTagStream(tagger, 500000000, ...
%         [SNSPD_channel_1H,SNSPD_channel_1V,SNSPD_channel_2H,SNSPD_channel_2V,clock_channel]);
% stream.startFor(1e12); % 1s
% while stream.isRunning()
%     pause(0.1)
% end
% 
% data = stream.getData();
% stamps_data=double(data.getTimestamps());
% channel_data=double(data.getChannels());


load('example_data.mat')
stamps_data=double(data_save);
channel_data=double(data_save);

% Input:
% stamps_data - timestamps from TDC.
% channel_data - channels of each timestamps.
% channel - all channel numbers of input channels,the first to fourth channels are detector channel,the fifth is clock channel.  

% Output:
% tag - timestamps which has be processed.
% N - the number of clock signals.
[tag,N]=tdcport(stamps_data,channel_data,channel);

