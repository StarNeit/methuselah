include $(top_srcdir)/src/Makefile.include

AM_CPPFLAGS += -I$(top_srcdir)/src \
  -I$(top_builddir)/src/qt \
  -I$(top_builddir)/src/qt/forms \
  $(PROTOBUF_CFLAGS) \
  $(QR_CFLAGS)
bin_PROGRAMS = methuselah-qt
noinst_LIBRARIES = libmethuselahqt.a
SUBDIRS = . $(BUILD_TEST_QT)
DIST_SUBDIRS = . test

# methuselah qt core #
QT_TS = \
  locale/methuselah_bar.ts \
  locale/methuselah_bg.ts \
  locale/methuselah_ca.ts \
  locale/methuselah_cmn.ts \
  locale/methuselah_cs.ts \
  locale/methuselah_da.ts \
  locale/methuselah_de.ts \
  locale/methuselah_el.ts \
  locale/methuselah_en.ts \
  locale/methuselah_eo.ts \
  locale/methuselah_es.ts \
  locale/methuselah_fi.ts \
  locale/methuselah_fr.ts \
  locale/methuselah_hu_HU.ts \
  locale/methuselah_it.ts \
  locale/methuselah_lv_LV.ts \
  locale/methuselah_nb.ts \
  locale/methuselah_nl.ts \
  locale/methuselah_pl.ts \
  locale/methuselah_pt.ts \
  locale/methuselah_pt_BR.ts \
  locale/methuselah_ru.ts \
  locale/methuselah_sk.ts \
  locale/methuselah_sv.ts \
  locale/methuselah_tr.ts \
  locale/methuselah_vi.ts \
  locale/methuselah_zh_CN.ts \
  locale/methuselah_zh_HK.ts

QT_FORMS_UI = \
  forms/aboutdialog.ui \
  forms/addressbookpage.ui \
  forms/askpassphrasedialog.ui \
  forms/coincontroldialog.ui \
  forms/darksendconfig.ui \
  forms/editaddressdialog.ui \
  forms/helpmessagedialog.ui \
  forms/intro.ui \
  forms/openuridialog.ui \
  forms/optionsdialog.ui \
  forms/overviewpage.ui \
  forms/paperwalletdialog.ui \
  forms/receivecoinsdialog.ui \
  forms/receiverequestdialog.ui \
  forms/rpcconsole.ui \
  forms/sendcoinsdialog.ui \
  forms/sendcoinsentry.ui \
  forms/signverifymessagedialog.ui \
  forms/transactiondescdialog.ui \
  forms/masternodelist.ui

QT_MOC_CPP = \
  moc_addressbookpage.cpp \
  moc_addresstablemodel.cpp \
  moc_askpassphrasedialog.cpp \
  moc_methuselahaddressvalidator.cpp \
  moc_methuselahamountfield.cpp \
  moc_methuselahgui.cpp \
  moc_methuselahunits.cpp \
  moc_clientmodel.cpp \
  moc_coincontroldialog.cpp \
  moc_coincontroltreewidget.cpp \
  moc_csvmodelwriter.cpp \
  moc_darksendconfig.cpp \
  moc_editaddressdialog.cpp \
  moc_guiutil.cpp \
  moc_intro.cpp \
  moc_macdockiconhandler.cpp \
  moc_macnotificationhandler.cpp \
  moc_monitoreddatamapper.cpp \
  moc_notificator.cpp \
  moc_openuridialog.cpp \
  moc_optionsdialog.cpp \
  moc_optionsmodel.cpp \
  moc_overviewpage.cpp \
  moc_peertablemodel.cpp \
  moc_paymentserver.cpp \
  moc_qvalidatedlineedit.cpp \
  moc_qvaluecombobox.cpp \
  moc_receivecoinsdialog.cpp \
  moc_receiverequestdialog.cpp \
  moc_recentrequeststablemodel.cpp \
  moc_rpcconsole.cpp \
  moc_sendcoinsdialog.cpp \
  moc_sendcoinsentry.cpp \
  moc_signverifymessagedialog.cpp \
  moc_splashscreen.cpp \
  moc_trafficgraphwidget.cpp \
  moc_transactiondesc.cpp \
  moc_transactiondescdialog.cpp \
  moc_transactionfilterproxy.cpp \
  moc_transactiontablemodel.cpp \
  moc_transactionview.cpp \
  moc_utilitydialog.cpp \
  moc_verticallabel.cpp \
  moc_walletframe.cpp \
  moc_walletmodel.cpp \
  moc_walletview.cpp \
  moc_masternodelist.cpp

METHUSELAH_MM = \
  macdockiconhandler.mm \
  macnotificationhandler.mm

QT_MOC = \
  methuselah.moc \
  intro.moc \
  overviewpage.moc \
  rpcconsole.moc

QT_QRC_CPP = qrc_methuselah.cpp
QT_QRC = methuselah.qrc

PROTOBUF_CC = paymentrequest.pb.cc
PROTOBUF_H = paymentrequest.pb.h
PROTOBUF_PROTO = paymentrequest.proto

METHUSELAH_QT_H = \
  addressbookpage.h \
  addresstablemodel.h \
  askpassphrasedialog.h \
  methuselahaddressvalidator.h \
  methuselahamountfield.h \
  methuselahgui.h \
  methuselahunits.h \
  clientmodel.h \
  coincontroldialog.h \
  coincontroltreewidget.h \
  csvmodelwriter.h \
  darksendconfig.h \
  editaddressdialog.h \
  guiconstants.h \
  guiutil.h \
  intro.h \
  macdockiconhandler.h \
  macnotificationhandler.h \
  monitoreddatamapper.h \
  notificator.h \
  openuridialog.h \
  optionsdialog.h \
  optionsmodel.h \
  overviewpage.h \
  paymentrequestplus.h \
  paymentserver.h \
  peertablemodel.h \
  qvalidatedlineedit.h \
  qvaluecombobox.h \
  receivecoinsdialog.h \
  receiverequestdialog.h \
  recentrequeststablemodel.h \
  rpcconsole.h \
  sendcoinsdialog.h \
  sendcoinsentry.h \
  signverifymessagedialog.h \
  splashscreen.h \
  trafficgraphwidget.h \
  transactiondesc.h \
  transactiondescdialog.h \
  transactionfilterproxy.h \
  transactionrecord.h \
  transactiontablemodel.h \
  transactionview.h \
  utilitydialog.h \
  verticallabel.h \
  walletframe.h \
  walletmodel.h \
  walletmodeltransaction.h \
  walletview.h \
  winshutdownmonitor.h \
  masternodelist.h

RES_ICONS = \
  res/icons/add.png \
  res/icons/address-book.png \
  res/icons/methuselah.ico \
  res/icons/methuselah.png \
  res/icons/methuselah_testnet.ico \
  res/icons/methuselah_testnet.png \
  res/icons/clock1.png \
  res/icons/clock2.png \
  res/icons/clock3.png \
  res/icons/clock4.png \
  res/icons/clock5.png \
  res/icons/configure.png \
  res/icons/connect0_16.png \
  res/icons/connect1_16.png \
  res/icons/connect2_16.png \
  res/icons/connect3_16.png \
  res/icons/connect4_16.png \
  res/icons/debugwindow.png \
  res/icons/edit.png \
  res/icons/editcopy.png \
  res/icons/editpaste.png \
  res/icons/export.png \
  res/icons/filesave.png \
  res/icons/history.png \
  res/icons/key.png \
  res/icons/lock_closed.png \
  res/icons/lock_open.png \
  res/icons/overview.png \
  res/icons/print.png \
  res/icons/qrcode.png \
  res/icons/quit.png \
  res/icons/receive.png \
  res/icons/remove.png \
  res/icons/send.png \
  res/icons/synced.png \
  res/icons/toolbar.png \
  res/icons/toolbar_testnet.png \
  res/icons/transaction0.png \
  res/icons/transaction2.png \
  res/icons/transaction_conflicted.png \
  res/icons/tx_inout.png \
  res/icons/tx_input.png \
  res/icons/tx_output.png \
  res/icons/tx_mined.png \
  res/icons/drkblue_editpaste.png \
  res/icons/drkblue_address-book.png \
  res/icons/drkblue_editcopy.png \
  res/icons/drkblue_remove.png \
  res/icons/browse.png


METHUSELAH_QT_CPP = \
  methuselah.cpp \
  methuselahaddressvalidator.cpp \
  methuselahamountfield.cpp \
  methuselahgui.cpp \
  methuselahunits.cpp \
  clientmodel.cpp \
  csvmodelwriter.cpp \
  darksendconfig.cpp \
  guiutil.cpp \
  intro.cpp \
  monitoreddatamapper.cpp \
  notificator.cpp \
  optionsdialog.cpp \
  optionsmodel.cpp \
  qvalidatedlineedit.cpp \
  qvaluecombobox.cpp \
  rpcconsole.cpp \
  splashscreen.cpp \
  trafficgraphwidget.cpp \
  utilitydialog.cpp \
  verticallabel.cpp \
  winshutdownmonitor.cpp

if ENABLE_WALLET
METHUSELAH_QT_CPP += \
  addressbookpage.cpp \
  addresstablemodel.cpp \
  askpassphrasedialog.cpp \
  coincontroldialog.cpp \
  coincontroltreewidget.cpp \
  darksendconfig.cpp \
  editaddressdialog.cpp \
  openuridialog.cpp \
  overviewpage.cpp \
  paymentrequestplus.cpp \
  paymentserver.cpp \
  peertablemodel.cpp \
  receivecoinsdialog.cpp \
  receiverequestdialog.cpp \
  recentrequeststablemodel.cpp \
  sendcoinsdialog.cpp \
  sendcoinsentry.cpp \
  signverifymessagedialog.cpp \
  transactiondesc.cpp \
  transactiondescdialog.cpp \
  transactionfilterproxy.cpp \
  transactionrecord.cpp \
  transactiontablemodel.cpp \
  transactionview.cpp \
  verticallabel.cpp \
  walletframe.cpp \
  walletmodel.cpp \
  walletmodeltransaction.cpp \
  walletview.cpp
endif

RES_IMAGES = \
  res/images/about.png \
  res/images/splash.png \
  res/images/splash_testnet.png \
  res/images/paper_wallet.png \
  res/images/methuselah_logo_horizontal.png \
  res/images/drkblue_downArrow.png \
  res/images/drkblue_downArrow_small.png \
  res/images/drkblue_upArrow_small.png \
  res/images/drkblue_leftArrow_small.png \
  res/images/drkblue_rightArrow_small.png \
  res/images/drkblue_qtreeview_selected.png \
  res/images/methuselah_main_hg.png \
  res/images/methuselah_theme1_hg.png \
  res/images/methuselah_theme2_hg.png \
  res/images/methuselah_theme3_hg.png

RES_CSS = \
  res/css/default.css 
  
RES_MOVIES = $(wildcard res/movies/spinner-*.png)

SAP_RC = res/methuselah-qt-res.rc

libmethuselahqt_a_CPPFLAGS = $(AM_CPPFLAGS) $(QT_INCLUDES) \
  -I$(top_srcdir)/src/qt/forms $(QT_DBUS_INCLUDES)
libmethuselahqt_a_SOURCES = $(METHUSELAH_QT_CPP) $(METHUSELAH_QT_H) $(QT_FORMS_UI) \
  $(QT_QRC) $(QT_TS) $(PROTOBUF_PROTO) $(RES_ICONS) $(RES_IMAGES) $(RES_MOVIES) $(RES_CSS)

nodist_libmethuselahqt_a_SOURCES = $(QT_MOC_CPP) $(QT_MOC) $(PROTOBUF_CC) \
  $(PROTOBUF_H) $(QT_QRC_CPP)

BUILT_SOURCES = $(nodist_libmethuselahqt_a_SOURCES)

#Generating these with a half-written protobuf header leads to wacky results.
#This makes sure it's done.
$(QT_MOC): $(PROTOBUF_H)
$(QT_MOC_CPP): $(PROTOBUF_H)

# methuselah-qt binary #
methuselah_qt_CPPFLAGS = $(AM_CPPFLAGS) $(QT_INCLUDES) \
  -I$(top_srcdir)/src/qt/forms
methuselah_qt_SOURCES = methuselah.cpp
if TARGET_DARWIN
  methuselah_qt_SOURCES += $(METHUSELAH_MM)
endif
if TARGET_WINDOWS
  methuselah_qt_SOURCES += $(SAP_RC)
endif
methuselah_qt_LDADD = libmethuselahqt.a $(LIBMETHUSELAH_SERVER)
if ENABLE_WALLET
methuselah_qt_LDADD += $(LIBMETHUSELAH_WALLET)
endif
methuselah_qt_LDADD += $(LIBMETHUSELAH_CLI) $(LIBMETHUSELAH_COMMON) $(LIBLEVELDB) $(LIBMEMENV) \
  $(BOOST_LIBS) $(QT_LIBS) $(QT_DBUS_LIBS) $(QR_LIBS) $(PROTOBUF_LIBS) $(BDB_LIBS)
methuselah_qt_LDFLAGS = $(QT_LDFLAGS)

# forms/foo.h -> forms/ui_foo.h
QT_FORMS_H=$(join $(dir $(QT_FORMS_UI)),$(addprefix ui_, $(notdir $(QT_FORMS_UI:.ui=.h))))

#locale/foo.ts -> locale/foo.qm
QT_QM=$(QT_TS:.ts=.qm)

.PHONY: FORCE
.SECONDARY: $(QT_QM)

methuselahstrings.cpp: FORCE
	$(MAKE) -C $(top_srcdir)/src qt/methuselahstrings.cpp

translate: methuselahstrings.cpp $(QT_FORMS_UI) $(QT_FORMS_UI) $(METHUSELAH_QT_CPP) $(METHUSELAH_QT_H) $(METHUSELAH_MM)
	@test -n $(LUPDATE) || echo "lupdate is required for updating translations"
	@QT_SELECT=$(QT_SELECT) $(LUPDATE) $^ -locations relative -no-obsolete -ts locale/methuselah_en.ts

$(QT_QRC_CPP): $(QT_QRC) $(QT_QM) $(QT_FORMS_H) $(RES_ICONS) $(RES_IMAGES) $(RES_MOVIES) $(RES_CSS) $(PROTOBUF_H)
	@cd $(abs_srcdir); test -f $(RCC) && QT_SELECT=$(QT_SELECT) $(RCC) -name methuselah -o $(abs_builddir)/$@ $< || \
	  echo error: could not build $@
	$(SED) -e '/^\*\*.*Created:/d' $@ > $@.n && mv $@{.n,}
	$(SED) -e '/^\*\*.*by:/d' $@  > $@.n && mv $@{.n,}

CLEANFILES = $(BUILT_SOURCES) $(QT_QM) $(QT_FORMS_H) *.gcda *.gcno
