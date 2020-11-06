USE [NHMFDServerDB]
GO

/****** Object:  Table [dbo].[Toll_Operator]    Script Date: 07/14/2020 20:37:47 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[Toll_Operator](
	[AutoID] [int] IDENTITY(1,1) NOT NULL,
	[Name] [nvarchar](50) NULL,
	[UserName] [nvarchar](50) NULL,
	[Password] [nvarchar](50) NULL,
	[Permission] [image] NULL,
	[Remark] [nvarchar](1024) NULL,
	[Reserved1] [nvarchar](50) NULL,
	[Reserved2] [nvarchar](50) NULL,
	[Reserved3] [nvarchar](50) NULL,
 CONSTRAINT [PK_TOLL_OPERATOR] PRIMARY KEY CLUSTERED 
(
	[AutoID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]

GO


