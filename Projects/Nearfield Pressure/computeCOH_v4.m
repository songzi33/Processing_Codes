function [cohmap f X Y cpsd xpsd ypsd] = computeCOH_v4(src_dir,flist)
%This function is designed to work on the filtered (non-averaged)
%microphone data. It is designed to work with _proc mat-files 1.1, and uses
%the temporary coherence code, coherence_v2.m.

    %Processing channel constants
    pp.NFCh = 1:8; %nearfield microphone channel for correlations
    pp.CorCh = {'ff.pblocks.smp(:,2,:)','ff.pblocks.smp(:,5,:)','ff.pblocks.smp(:,7,:)','ff.pblocks.smp(:,9,:)','nf.pblocks.smp(:,4,:)'}; %correlation channels - either nearfield or farfield

    %DAQ constants
    pp.FS = 200000; %data acquisition frequency, in Hz
    pp.sBS = 8192; %processing block size
    
    %initialize variables
    Lf = length(flist);
    Lc = length(pp.NFCh);
    Lcor = length(pp.CorCh);
    nfrq = ceil((pp.sBS+1)/2);
    X = zeros(Lf,Lc);
    Y = X;
    cohmap = zeros(Lf,Lc,Lcor,nfrq);
    cpsd = cohmap;
    xpsd = cohmap;
    ypsd = cohmap;
    
    h = waitbar(0,'Calculating...0% Complete');
    for n = 1:Lf  %file number  
        %determine x and y locations for microphone signals
        data = load([src_dir filesep flist{n}]);
        X(n,:) = data.phys.x;
        Y(n,:) = data.phys.y;
        
        for nn = 1:Lcor %cor channel number
            %Get cor channel data
            cor = squeeze(eval(['data.',pp.CorCh{nn}]));
              
            %compute coherence
            for nnn = 1:Lc %nearfield channel number
                ncor = squeeze(data.nf.pblocks.smp(:,nnn,:)); %nearfield correlation data
                [cohmap(n,nnn,nn,:), f, cpsd(n,nnn,nn,:), xpsd(n,nnn,nn,:), ypsd(n,nnn,nn,:)] = coherence_v2(ncor,cor,pp.FS,pp.sBS,@hann);          
            end        
        end
        waitbar(n/Lf,h,['Calculating...',num2str(round(n/Lf*100)),'% Complete']);
    end
    close(h);
    
    %Reshape matrices
    [X Y cohmap cpsd xpsd ypsd] = ReshapeGrid(X,Y,cohmap,cpsd, xpsd, ypsd);
end