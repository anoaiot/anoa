Summary:IGOS Nusantara SDK
Name:ignsdk-iot
Version:0.1
Release:2
License:BSD
Group:System Environment/Base
URL:http://igos-nusantara.or.id
Source0:http://github.com/anak10thn/ignsdk-qt/archive/%{version}.%{release}.zip
BuildRoot:%{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)
Requires:qt5-qtwebchannel
Requires:qt5-qtbase-mysql
Requires:qt5-qtbase
Requires:qt5-qtserialport
Requires:qt5-qtwebsockets
Requires:nodejs
Requires:sharkio
BuildRequires:qt5-qtwebchannel-devel
BuildRequires:gcc-c++
BuildRequires:qt5-qtbase-mysql-devel
BuildRequires:qt5-qtbase-devel
BuildRequires:qt5-qtserialport-devel
BuildRequires:qt5-qtwebsockets-devel
%description
IGOS Nusantara Software Development Kit For Internet of Things

%prep
%setup -q -n %{name}-%{version}.%{release}

%install
install -d -m 755 $RPM_BUILD_ROOT/usr/bin
install -d -m 755 $RPM_BUILD_ROOT/etc/ignsdk/board
qmake-qt5
make -j4
cp -rf bin/ignsdk-iot $RPM_BUILD_ROOT/usr/bin
cp -rf config/rpi2.json $RPM_BUILD_ROOT/etc/ignsdk/board

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root,-)
/usr/bin/ignsdk-iot
/etc/ignsdk/board/rpi2.json

%changelog
* Wed Mar 11 2015 ibnu yahya <anak10thn@gmail.com>
- Bump version to 0.1.1
