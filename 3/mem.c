#include <efi.h>
#include <efilib.h>

EFI_STATUS efi_main (EFI_HANDLE image, EFI_SYSTEM_TABLE *systab) {
	UINTN N = 0;
	EFI_MEMORY_DESCRIPTOR * md;
	UINTN md_size, md_key;
	UINT32 md_version;
	EFI_STATUS res = EFI_SUCCESS;

	InitializeLib(image, systab);
	res = uefi_call_wrapper(systab->BootServices->GetMemoryMap, 5, &N, NULL, NULL, NULL, NULL);
	Print(L"Size requared: %d\n\r", N);

	return EFI_SUCCESS;
}
