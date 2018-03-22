// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#ifndef _OE_EC_H
#define _OE_EC_H

#include "../result.h"
#include "../types.h"
#include "sha.h"

OE_EXTERNC_BEGIN

/* Opaque representation of an EC public key */
typedef struct _OE_EC
{
    /* Internal private implementation */
    uint64_t impl[4];
} OE_EC_KEY;

/**
 * Reads a public EC key from PEM data.
 *
 * This function loads an EC key from a data buffer that contains a PEM
 * representation of an EC key with the following format.
 *
 *     -----BEGIN EC PRIVATE KEY-----
 *     ...
 *     -----END EC PRIVATE KEY-----
 *
 * @param pemData - pointer to zero-terminated PEM key representation
 * @param pemSize - size of the pemData buffer including the zero-terminator
 * @param privateKey - private key structure (pass to OE_ECFree() to free)
 *
 * @return OE_OK upon success
 */
OE_Result OE_ECReadPrivateKeyFromPEM(
    const uint8_t* pemData,
    size_t pemSize,
    OE_EC_KEY* privateKey);

/**
 * Reads a public EC key from PEM data.
 *
 * This function loads an EC key from a data buffer that contains a PEM
 * representation of an EC key with the following format.
 *
 *     -----BEGIN PUBLIC KEY-----
 *     ...
 *     -----END PUBLIC KEY-----
 *
 * @param pemData - pointer to zero-terminated PEM key representation
 * @param pemSize - size of the pemData buffer including the zero-terminator
 * @param publicKey - public key structure (pass to OE_ECFree() to free)
 *
 * @return OE_OK upon success
 */
OE_Result OE_ECReadPublicKeyFromPEM(
    const uint8_t* pemData,
    size_t pemSize,
    OE_EC_KEY* publicKey);

/**
 * Reads a public EC key from PEM data.
 *
 * This function loads an EC key from a data buffer that contains a PEM
 * representation of an EC key with the following format.
 *
 *     -----BEGIN EC PRIVATE KEY-----
 *     ...
 *     -----END EC PRIVATE KEY-----
 *
 * @param pemData - pointer to zero-terminated PEM key representation
 * @param pemSize - size of the pemData buffer including the zero-terminator
 * @param privateKey - private key structure (pass to OE_ECFree() to release)
 *
 * @return OE_OK upon success
 */
OE_Result OE_ECReadPrivateKeyFromPEM(
    const uint8_t* pemData,
    size_t pemSize,
    OE_EC_KEY* privateKey);

/**
 * Reads a public EC key from PEM data.
 *
 * This function loads an EC key from a data buffer that contains a PEM
 * representation of an EC key with the following format.
 *
 *     -----BEGIN PUBLIC KEY-----
 *     ...
 *     -----END PUBLIC KEY-----
 *
 * @param pemData - pointer to zero-terminated PEM key representation
 * @param pemSize - size of the pemData buffer including the zero-terminator
 * @param publicKey - public key structure (pass to OE_ECFree() to free)
 *
 * @return OE_OK upon success
 */
OE_Result OE_ECReadPublicKeyFromPEM(
    const uint8_t* pemData,
    size_t pemSize,
    OE_EC_KEY* publicKey);

/**
 * Write an EC private key to PEM format
 *
 * This function writes an EC private key to PEM format, which has the
 * following form.
 *
 *     -----BEGIN PUBLIC KEY-----
 *     ...
 *     -----END PUBLIC KEY-----
 *
 * @param privateKey - private key to be written
 * @param pemData - buffer where PEM data is written
 * @param[in,out] pemSize - size of the PEM buffer on input; size of the actual
 *     PEM data on output. If the former is less than the latter, this function
 *     returns OE_BUFFER_TOO_SMALL.
 *
 * @return OE_OK upon success
 * @return OE_BUFFER_TOO_SMALL PEM buffer is not big engough
 */
OE_Result OE_ECWritePrivateKeyToPEM(
    const OE_EC_KEY* privateKey,
    uint8_t* pemData,
    size_t* pemSize);

/**
 * Write an EC public key to PEM format
 *
 * This function writes an EC public key to PEM form, which has the
 * following form.
 *
 *     -----BEGIN PUBLIC KEY-----
 *     ...
 *     -----END PUBLIC KEY-----
 *
 * @param publicKey - public key to be written
 * @param pemData - buffer where PEM data is written
 * @param[in,out] pemSize - size of the PEM buffer on input; size of the actual
 *     PEM data on output. If the former is less than the latter, this function
 *     returns OE_BUFFER_TOO_SMALL.
 *
 * @return OE_OK upon success
 * @return OE_BUFFER_TOO_SMALL PEM buffer is not big engough
 */
OE_Result OE_ECWritePublicKeyToPEM(
    const OE_EC_KEY* publicKey,
    uint8_t* pemData,
    size_t* pemSize);

/**
 * Releases an EC key structure
 *
 * This function releases an EC public key sturcture that was created
 * by one of the functions in this module.
 *
 * @param key - pointer to EC public key struture.
 *
 * @return OE_OK upon success
 */
OE_Result OE_ECFree(OE_EC_KEY* key);

/**
 * Digitaly signs a message with an EC private key
 *
 * This function uses an EC private key to sign a message with the given hash.
 *
 * @param privateKey - EC private key
 * @param hash - SHA-256 hash of the message being signed
 * @param signature - signature buffer (may be null)
 * @param[in,out] signatureSize - size of signature buffer on input; size of
 *     actual signature on output. If the former is less than the latter, this
 *     function returns OE_BUFFER_TOO_SMALL.
 *
 * @return OE_OK on success
 * @return OE_BUFFER_TOO_SMALL if signature buffer is too small
 */
OE_Result OE_ECSign(
    const OE_EC_KEY* privateKey,
    const OE_SHA256* hash,
    uint8_t* signature,
    size_t* signatureSize);

/**
 * Verify that a message was signed by a given EC key
 *
 * This function verifies that a message (with the given hash) was signed by a
 * a given EC key.
 *
 * @param publicKey - EC public key
 * @param hash - SHA-256 hash of the message being verified
 * @param signature - expected signature
 * @param signatureSize - size in bytes of the expected signature
 *
 * @return OE_OK if the message was signeded with the given certificate
 */
OE_Result OE_ECVerify(
    const OE_EC_KEY* publicKey,
    const OE_SHA256* hash,
    const uint8_t* signature,
    size_t signatureSize);

/**
 * Generate an EC private-public key pair
 *
 * This function generate an EC private-public key pair from the given
 * parameters.
 *
 * @param curveName - EC curve name (e.g., "secp521r1")
 * @param privateKey - generate private key
 * @param publicKey - generate public key
 *
 * @return OE_OK on success
 */
OE_Result OE_ECGenerate(
    const char* curveName,
    OE_EC_KEY* privateKey,
    OE_EC_KEY* publicKey);

OE_EXTERNC_END

#endif /* _OE_EC_H */
