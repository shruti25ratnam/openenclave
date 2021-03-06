# SGX1 with Flexible Launch Control (FLC) Prerequisites on Windows

## [Intel Platform Software for Windows (PSW) v2.7](http://registrationcenter-download.intel.com/akdlm/irc_nas/16607/Intel%20SGX%20PSW%20for%20Windows%20v2.7.101.2.exe)

The PSW only needs to be manually installed if you are running on Windows Server
2016 or a version of Windows client lower than 1709. It should be installed automatically 
with Windows Update on newer versions of Windows client and Windows Server 2019.
You can check your version of Windows by running `winver` on the command line.
Ensure that you have the latest drivers on Windows 10 and Windows Server 2019 by checking for updates and installing all updates.

After unpacking the self-extracting ZIP executable, install the *PSW_EXE_RS2_and_before* version:
```cmd
C:\Intel SGX PSW for Windows v2.7.101.2\PSW_EXE_RS2_and_before\Intel(R)_SGX_Windows_x64_PSW_2.7.101.2.exe"
```

## [Azure DCAP client for Windows](https://github.com/Microsoft/Azure-DCAP-Client/tree/master/src/Windows) [optional]

Note that this is optional since you can choose an alternate implementation of the DCAP client or create your own.
The Azure DCAP client for Windows is necessary if you would like to perform enclave attestation on a Azure Confidential Computing VM. It is available from [nuget.org](https://www.nuget.org/packages/Microsoft.Azure.DCAP/) and can be installed directly via command below.

```cmd
nuget.exe install Microsoft.Azure.DCAP -ExcludeVersion -Version 1.3.0 -OutputDirectory C:\oe_prereqs
```
This example assumes you would like to install the package to `C:\oe_prereqs`.

## [Intel Data Center Attestation Primitives (DCAP) Libraries v1.6](http://registrationcenter-download.intel.com/akdlm/irc_nas/16620/Intel%20SGX%20DCAP%20for%20Windows%20v1.6.100.2.exe)
After unpacking the self-extracting ZIP executable, you can refer to the *Intel SGX DCAP Windows SW Installation Guide.pdf*
for more details on how to install the contents of the package.

The following summary will assume that the contents were extracted to `C:\Intel SGX DCAP for Windows v1.6.100.2`:

### Install the Intel DCAP nuget packages
The standalone `nuget.exe` [CLI tool](https://dist.nuget.org/win-x86-commandline/latest/nuget.exe) can be used to do this from the command prompt:

```cmd
nuget.exe install DCAP_Components -ExcludeVersion -Source "C:\Intel SGX DCAP for Windows v1.6.100.2\nuget" -OutputDirectory c:\oe_prereqs
nuget.exe install EnclaveCommonAPI -ExcludeVersion -Source "C:\Intel SGX DCAP for Windows v1.6.100.2\nuget" -OutputDirectory c:\oe_prereqs
```

### Install the Intel DCAP driver

1. Unzip the required drivers from the extracted subfolders:
    - For Windows Server 2016
      - `LC_driver_WinServer2016\Signed_*.zip`
      - `DCAP_INF\WinServer2016\Signed_*.zip`
    - For Windows Server 2019
      - `LC_driver_WinServer2019\Signed_*.zip`
      - `DCAP_INF\WinServer2019\Signed_*.zip`

   The following instructions will assume that these have been unzipped into the `LC_driver` and `DCAP_INF` folders respectively.

2. Allow the SGX Launch Configuration driver (LC_driver) to run:
    - From an elevated command prompt:
      ```cmd
      reg add HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\sgx_lc_msr\Parameters /v "SGX_Launch_Config_Optin" /t REG_DWORD /d 1
      reg query HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\sgx_lc_msr\Parameters /v "SGX_Launch_Config_Optin"
      ```
    - If the driver is already installed and running, the machine will need to be rebooted for the change to take effect.

3. Install the drivers:
    - `devcon.exe` from the [Windows Driver Kit for Windows 10](https://go.microsoft.com/fwlink/?linkid=2026156)
      can be used to install the drivers from an elevated command prompt:
      ```cmd
      devcon.exe install LC_driver\drivers\8e78fd6b-efeb-4952-ab0d-945e61c164ba\sgx_base_dev.inf root\SgxLCDevice
      devcon.exe install DCAP_INF\drivers\08cc8440-9f38-4635-9685-cdbf476666fa\sgx_dcap_dev.inf root\SgxLCDevice_DCAP
      ```
    - The hash values in the paths may be different from the above commands, please update them accordingly.
    - Note that `devcon.exe` is usually installed to `C:\Program Files (x86)\Windows Kits\10\tools\x64` which is not in the PATH environment variable by default.
