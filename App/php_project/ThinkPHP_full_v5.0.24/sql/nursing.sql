DROP TABLE IF EXISTS `yunzhi_nursing`;
CREATE TABLE `yunzhi_nursing` (
`id` bigint(20) unsigned NOT NULL AUTO_INCREMENT COMMENT '自增长id',
`project_type` tinyint(4) unsigned NOT NULL DEFAULT '0' COMMENT '项目：0-母乳；1-配方奶；2-开水；3-便便',
`project_number` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '项目的数量或者次数',
`project_date` DATE NULL DEFAULT NULL COMMENT '项目日期',
`project_time` TIME NULL DEFAULT NULL COMMENT '项目时间',
`project_comments` varchar(2048) COLLATE utf8mb4_unicode_ci NOT NULL COMMENT '项目备注',
`create_time` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '创建时间',
`update_time` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '更新时间',
PRIMARY KEY (`id`),
UNIQUE KEY `tdt`(`project_type`, `project_date`, `project_time`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci COMMENT='喂奶神器表';


INSERT INTO `yunzhi_nursing` VALUES ('1', 1, '100', '2020-10-01', '21:15', '', '1601558121', '1601558121');
