// Copyright (c) 2017 The STRAKS developers
// Copyright (c) 2017-2018 The Methuselah Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef METHUSELAH_QT_METHUSELAHADDRESSVALIDATOR_H
#define METHUSELAH_QT_METHUSELAHADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class MethuselahAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit MethuselahAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** Methuselah address widget validator, checks for a valid methuselah address.
 */
class MethuselahAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit MethuselahAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // METHUSELAH_QT_METHUSELAHADDRESSVALIDATOR_H
