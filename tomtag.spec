Name:           tomtag
Version:        0.11
Release:        1
Summary:        Time tag correlation library
License:        MIT
URL:            https://github.com/Thomas-Jaeken/tomtag

%description
This package holds several functions to process raw
timetags that would be output by a tagger like e.g.
a UQD Logic16.

%package -n python3-tomtag
Summary:        Time tag correlation library
License:        MIT
Provides:       tomtag

BuildRequires:  python3-devel
BuildRequires:  python3-setuptools
BuildRequires:  python3-build
BuildRequires:  python3-numpy
BuildRequires:  gcc

%description -n python3-tomtag
This package holds several functions to process raw
timetags that would be output by a tagger like e.g.
a UQD Logic16.

%prep
# we have no source, so nothing here

%build
python3 -m build -w
unzip dist/*.whl -d dist/files/

%install
mkdir -p %{buildroot}/usr/lib/python3.12/site-packages/tomtag
mkdir -p %{buildroot}/usr/lib/python3.12/site-packages/tomtag-0.11.dist-info

install -m 755 dist/files/tomtag/* %{buildroot}/usr/lib/python3.12/site-packages/tomtag/
install -m 755 dist/files/tomtag-0.11.dist-info/* %{buildroot}/usr/lib/python3.12/site-packages/tomtag-0.11.dist-info/
install -m 755 dist/files/tomtag.cpython-312-x86_64-linux-gnu.so %{buildroot}/usr/lib/python3.12/site-packages/


%files
 /usr/lib/python3.12/site-packages/*

%changelog
# let's skip this for now