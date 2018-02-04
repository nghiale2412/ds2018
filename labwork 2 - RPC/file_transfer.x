struct file{
	char *file_name;
	char *file_content;
};

program FILE_TRANSFER_PROG
{
	version FILE_TRANSFER_VERS{
			int SEND_FILE(file) = 1;
	} = 1;
} = 99;