/*
 * Copyright (C) 2012 Robin Burchell <robin+nemo@viroteck.net>
 *
 * You may use this file under the terms of the BSD license as follows:
 *
 * "Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *   * Neither the name of Nemo Mobile nor the names of its contributors
 *     may be used to endorse or promote products derived from this
 *     software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
 */

#ifndef SEASIDEPERSON_H
#define SEASIDEPERSON_H

// Qt
#include <QObject>
#include <QUrl>

// Mobility
#include <QContact>

QTM_USE_NAMESPACE

class SeasidePerson : public QObject
{
    Q_OBJECT
    Q_ENUMS(DetailTypes)

public:
    /**
     * Identifiers of contact details for the UI.
     */
    enum DetailTypes {
        // Name
        FirstNameType,
        LastNameType,
        MiddleNameType,
        CompanyType,
        NickType,
        TitleType,
        // Phone
        PhoneHomeType,
        PhoneWorkType,
        PhoneMobileType,
        PhoneFaxType,
        PhonePagerType,
        // Email
        EmailHomeType,
        EmailWorkType,
        EmailOtherType
    };

    explicit SeasidePerson(QObject *parent = 0);
    ~SeasidePerson();

    Q_PROPERTY(int id READ id)
    int id() const;

    Q_PROPERTY(QString firstName READ firstName WRITE setFirstName NOTIFY firstNameChanged)
    QString firstName() const;
    void setFirstName(const QString &name);

    Q_PROPERTY(QString lastName READ lastName WRITE setLastName NOTIFY lastNameChanged)
    QString lastName() const;
    void setLastName(const QString &name);

    Q_PROPERTY(QString sectionBucket READ sectionBucket NOTIFY displayLabelChanged)
    QString sectionBucket() const;
    Q_PROPERTY(QString displayLabel READ displayLabel NOTIFY displayLabelChanged)
    QString displayLabel() const;

    Q_PROPERTY(QString companyName READ companyName WRITE setCompanyName NOTIFY companyNameChanged)
    QString companyName() const;
    void setCompanyName(const QString &name);

    Q_PROPERTY(bool favorite READ favorite WRITE setFavorite NOTIFY favoriteChanged)
    bool favorite() const;
    void setFavorite(bool favorite);

    Q_PROPERTY(QUrl avatarPath READ avatarPath WRITE setAvatarPath NOTIFY avatarPathChanged)
    QUrl avatarPath() const;
    void setAvatarPath(QUrl avatarPath);

    Q_PROPERTY(QStringList phoneNumbers READ phoneNumbers WRITE setPhoneNumbers NOTIFY phoneNumbersChanged)
    QStringList phoneNumbers() const;
    void setPhoneNumbers(const QStringList &phoneNumbers);

    Q_PROPERTY(QList<int> phoneNumberTypes READ phoneNumberTypes NOTIFY phoneNumberTypesChanged)
    QList<int> phoneNumberTypes() const;
    Q_INVOKABLE void setPhoneNumberType(int which, DetailTypes type);

    Q_PROPERTY(QStringList emailAddresses READ emailAddresses WRITE setEmailAddresses NOTIFY emailAddressesChanged)
    QStringList emailAddresses() const;
    void setEmailAddresses(const QStringList &emailAddresses);

    Q_PROPERTY(QList<int> emailAddressTypes READ emailAddressTypes NOTIFY emailAddressTypesChanged)
    QList<int> emailAddressTypes() const;
    Q_INVOKABLE void setEmailAddressType(int which, DetailTypes type);

    Q_PROPERTY(QStringList accountUris READ accountUris NOTIFY accountUrisChanged)
    QStringList accountUris() const;

    Q_PROPERTY(QStringList accountPaths READ accountPaths NOTIFY accountPathsChanged)
    QStringList accountPaths() const;

    QContact contact() const;
    void setContact(const QContact &contact);

    void recalculateDisplayLabel();

signals:
    void contactRemoved();
    void firstNameChanged();
    void lastNameChanged();
    void displayLabelChanged();
    void companyNameChanged();
    void favoriteChanged();
    void avatarPathChanged();
    void birthdayChanged();
    void phoneNumbersChanged();
    void phoneNumberTypesChanged();
    void emailAddressesChanged();
    void emailAddressTypesChanged();
    void accountUrisChanged();
    void accountPathsChanged();

private:
    // TODO: private class
    explicit SeasidePerson(const QContact &contact, QObject *parent = 0);
    QContact mContact;
    QString mDisplayLabel;

    friend class tst_SeasidePerson;
    friend class SeasidePeopleModelPriv;
};

Q_DECLARE_METATYPE(SeasidePerson *);

#endif // SEASIDEPERSON_H
