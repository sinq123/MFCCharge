USE [NHMFDServerDB]
GO
/****** Object:  Table [dbo].[Charge_DetType]    Script Date: 09/14/2020 12:21:22 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Charge_DetType](
	[AutoID] [int] IDENTITY(1,1) NOT NULL,
	[Code] [nvarchar](50) NULL,
	[Name] [nvarchar](50) NULL,
	[Remark] [nvarchar](1024) NULL,
	[Reserved1] [nvarchar](50) NULL,
	[Reserved2] [nvarchar](50) NULL,
	[Reserved3] [nvarchar](50) NULL,
 CONSTRAINT [PK_CHARGE_DETTYPE] PRIMARY KEY CLUSTERED 
(
	[AutoID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET IDENTITY_INSERT [dbo].[Charge_DetType] ON
INSERT [dbo].[Charge_DetType] ([AutoID], [Code], [Name], [Remark], [Reserved1], [Reserved2], [Reserved3]) VALUES (1, N'00', N'注册登记检验', NULL, NULL, NULL, NULL)
INSERT [dbo].[Charge_DetType] ([AutoID], [Code], [Name], [Remark], [Reserved1], [Reserved2], [Reserved3]) VALUES (2, N'01', N'在用车检验（定检）', NULL, NULL, NULL, NULL)
INSERT [dbo].[Charge_DetType] ([AutoID], [Code], [Name], [Remark], [Reserved1], [Reserved2], [Reserved3]) VALUES (3, N'02', N'临时检验', NULL, NULL, NULL, NULL)
INSERT [dbo].[Charge_DetType] ([AutoID], [Code], [Name], [Remark], [Reserved1], [Reserved2], [Reserved3]) VALUES (4, N'03', N'特殊检验', NULL, NULL, NULL, NULL)
INSERT [dbo].[Charge_DetType] ([AutoID], [Code], [Name], [Remark], [Reserved1], [Reserved2], [Reserved3]) VALUES (5, N'04', N'在用车检验（非定检）', NULL, NULL, NULL, NULL)
INSERT [dbo].[Charge_DetType] ([AutoID], [Code], [Name], [Remark], [Reserved1], [Reserved2], [Reserved3]) VALUES (6, N'技术等级评定', N'技术等级评定', NULL, NULL, NULL, NULL)
INSERT [dbo].[Charge_DetType] ([AutoID], [Code], [Name], [Remark], [Reserved1], [Reserved2], [Reserved3]) VALUES (7, N'注册登记检验//技术等级评定', N'注册登记检验//技术等级评定', NULL, NULL, NULL, NULL)
INSERT [dbo].[Charge_DetType] ([AutoID], [Code], [Name], [Remark], [Reserved1], [Reserved2], [Reserved3]) VALUES (8, N'在用车检验（定检）//技术等级评定', N'在用车检验（定检）//技术等级评定', NULL, NULL, NULL, NULL)
SET IDENTITY_INSERT [dbo].[Charge_DetType] OFF
