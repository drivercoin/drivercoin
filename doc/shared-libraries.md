Shared Libraries
================

## drivercoinconsensus

The purpose of this library is to make the verification functionality that is critical to Drivercoin's consensus available to other applications, e.g. to language bindings.

### API

The interface is defined in the C header `drivercoinconsensus.h` located in  `src/script/drivercoinconsensus.h`.

#### Version

`drivercoinconsensus_version` returns an `unsigned int` with the the API version *(currently at an experimental `0`)*.

#### Script Validation

`drivercoinconsensus_verify_script` returns an `int` with the status of the verification. It will be `1` if the input script correctly spends the previous output `scriptPubKey`.

##### Parameters
- `const unsigned char *scriptPubKey` - The previous output script that encumbers spending.
- `unsigned int scriptPubKeyLen` - The number of bytes for the `scriptPubKey`.
- `const unsigned char *txTo` - The transaction with the input that is spending the previous output.
- `unsigned int txToLen` - The number of bytes for the `txTo`.
- `unsigned int nIn` - The index of the input in `txTo` that spends the `scriptPubKey`.
- `unsigned int flags` - The script validation flags *(see below)*.
- `drivercoinconsensus_error* err` - Will have the error/success code for the operation *(see below)*.

##### Script Flags
- `drivercoinconsensus_SCRIPT_FLAGS_VERIFY_NONE`
- `drivercoinconsensus_SCRIPT_FLAGS_VERIFY_P2SH` - Evaluate P2SH ([BIP16](https://github.com/drivercoin/bips/blob/master/bip-0016.mediawiki)) subscripts
- `drivercoinconsensus_SCRIPT_FLAGS_VERIFY_DERSIG` - Enforce strict DER ([BIP66](https://github.com/drivercoin/bips/blob/master/bip-0066.mediawiki)) compliance

##### Errors
- `drivercoinconsensus_ERR_OK` - No errors with input parameters *(see the return value of `drivercoinconsensus_verify_script` for the verification status)*
- `drivercoinconsensus_ERR_TX_INDEX` - An invalid index for `txTo`
- `drivercoinconsensus_ERR_TX_SIZE_MISMATCH` - `txToLen` did not match with the size of `txTo`
- `drivercoinconsensus_ERR_DESERIALIZE` - An error deserializing `txTo`

### Example Implementations
- [NDrivercoin](https://github.com/NicolasDorier/NDrivercoin/blob/master/NDrivercoin/Script.cs#L814) (.NET Bindings)
- [node-libdrivercoinconsensus](https://github.com/bitpay/node-libdrivercoinconsensus) (Node.js Bindings)
- [java-libdrivercoinconsensus](https://github.com/dexX7/java-libdrivercoinconsensus) (Java Bindings)
