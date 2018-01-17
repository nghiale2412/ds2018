fprintf('>>>>>>>>> Choose your data file\n');
[baseName, folder] = uigetfile();
fullFileName = fullfile(folder, baseName);
data = load(fullFileName);
fprintf('>>>>>>>>> %s loaded successfully \n',baseName);