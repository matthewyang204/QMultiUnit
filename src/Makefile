all: refresh-translations

update-translations:
	lupdate *.cpp *.h *.ui -ts translations/QMultiUnit_ar.ts \
		translations/QMultiUnit_de_DE.ts \
		translations/QMultiUnit_es_ES.ts \
		translations/QMultiUnit_fr_FR.ts \
		translations/QMultiUnit_ko_KR.ts \
		translations/QMultiUnit_ru_RU.ts \
		translations/QMultiUnit_zh_CN.ts \
		translations/QMultiUnit_zh_TW.ts

refresh-release-translations:
	lrelease translations/QMultiUnit_ar.ts \
		translations/QMultiUnit_de_DE.ts \
		translations/QMultiUnit_es_ES.ts \
		translations/QMultiUnit_fr_FR.ts \
		translations/QMultiUnit_ko_KR.ts \
		translations/QMultiUnit_ru_RU.ts \
		translations/QMultiUnit_zh_CN.ts \
		translations/QMultiUnit_zh_TW.ts

refresh-translations: refresh-release-translations
refresh-all: update-translations refresh-release-translations
