--------------------------------------------------------------------------------
--
-- xmasEventSlayer.lua
--
--------------------------------------------------------------------------------
-- �̰� ����ϱ� ���� xmasEventCommon.lua�� load�ؾ� �Ѵ�.
-- Input  : SUM
-- Output : ItemClass, ItemType, OptionType
--------------------------------------------------------------------------------

-- select ItemClass
ItemClass 	= selectOne( ItemClassSlayerSet )

-- select ItemType, OptionType by SUM
ItemType 	= 0
OptionType 	= 0

if SUM <= 80 then
	ItemType = 2
	OptionType = selectOne( OptionInfoSet.Sum80 )

elseif SUM <= 140 then
	ItemType = 4
	OptionType = selectOne( OptionInfoSet.Sum140 )

elseif SUM <= 200 then
	ItemType = 5
	OptionType = selectOne( OptionInfoSet.Sum200 )

elseif SUM <= 250 then
	ItemType = 6
	OptionType = selectOne( OptionInfoSet.Sum250 )

else -- SUM < 300 then
	ItemType = 7
	OptionType = selectOne( OptionInfoSet.Sum300 )

end


