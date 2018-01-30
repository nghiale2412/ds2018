program FILE_TRANSFER_PROG
{
	version FILE_TRANSFER_VERS{
		int SEND_NAME(string) = 1;
		int SEND_CONTENT(string) = 2;
	} = 1;
} = 99;
