
void *operator_new(uint param_1)

{
  void *pvVar1;
  
  pvVar1 = operator_new(param_1);
  return pvVar1;
}

void main(int argc,  char **argv)
{
  N *obj;
  char *this_00;
  
  if (argc < 2) {
    _exit(1);
  }
  obj = (N *)operator_new(108);
  N::N(obj,5);
  this_00 = (char *)operator_new(108);
  N::N((N *)this_00,6);
  N::setAnnotation(obj,(*argv)[4]);
  (**(code **)*this_00)(this_00,obj);
  return;
}

void N::N(int param_1)
{
  *(int *)(this + 104) = param_1;
  return;
}

void N::setAnnotation(char *str)
{
  size_t len;
  
  len = strlen(str);
  memcpy(this + 4,str,len);
  return;
}

int N::operator_(N *param_1)

{
  return *(int *)(param_1 + 0x68) + *(int *)(this + 0x68);
}

int N::operator_(N *param_1)

{
  return *(int *)(this + 0x68) - *(int *)(param_1 + 0x68);
}