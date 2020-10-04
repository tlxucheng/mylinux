DROP TABLE IF EXISTS `yunzhi_nursing`;
CREATE TABLE `yunzhi_nursing` (
`id` bigint(20) unsigned NOT NULL AUTO_INCREMENT COMMENT '������id',
`project_type` tinyint(4) unsigned NOT NULL DEFAULT '0' COMMENT '��Ŀ��0-ĸ�飻1-�䷽�̣�2-��ˮ��3-���',
`project_number` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '��Ŀ���������ߴ���',
`project_date` DATE NULL DEFAULT NULL COMMENT '��Ŀ����',
`project_time` TIME NULL DEFAULT NULL COMMENT '��Ŀʱ��',
`project_comments` varchar(2048) COLLATE utf8mb4_unicode_ci NOT NULL COMMENT '��Ŀ��ע',
`create_time` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '����ʱ��',
`update_time` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '����ʱ��',
PRIMARY KEY (`id`),
UNIQUE KEY `tdt`(`project_type`, `project_date`, `project_time`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci COMMENT='ι��������';


INSERT INTO `yunzhi_nursing` VALUES ('1', 1, '100', '2020-10-01', '21:15', '', '1601558121', '1601558121');


DROP TABLE IF EXISTS `yunzhi_history`;
CREATE TABLE `yunzhi_history` (
`id` bigint(20) unsigned NOT NULL AUTO_INCREMENT COMMENT '������id',
`project_date` DATE NULL DEFAULT NULL COMMENT '��Ŀ����',
`breast_milk_number` int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'ĸ������',
`formula_number` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '�䷽������',
`boiling_water_number` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '��ˮ����',
`shit_number` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '�������',
`create_time` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '����ʱ��',
`update_time` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '����ʱ��',
PRIMARY KEY (`id`),
UNIQUE KEY `project_date`(`project_date`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci COMMENT='ι��������ʷ��';