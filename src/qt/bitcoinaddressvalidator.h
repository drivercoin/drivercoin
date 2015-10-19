// Copyright (c) 2011-2014 The Drivercoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_BITCOINADDRESSVALIDATOR_H
#define BITCOIN_QT_BITCOINADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class DrivercoinAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit DrivercoinAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** Drivercoin address widget validator, checks for a valid drivercoin address.
 */
class DrivercoinAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit DrivercoinAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // BITCOIN_QT_BITCOINADDRESSVALIDATOR_H
