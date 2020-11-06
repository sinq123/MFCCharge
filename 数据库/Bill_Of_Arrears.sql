USE [NHMFDServerDB]
GO

/****** Object:  Table [dbo].[Bill_Of_Arrears]    Script Date: 11/05/2020 15:18:32 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[Bill_Of_Arrears](
	[AutoID] [int] IDENTITY(1,1) NOT NULL,
	[Unit_Name] [nvarchar](200) NOT NULL,
	[Outstanding_Amount] [decimal](18, 4) NULL,
	[Amount_Received] [decimal](18, 4) NULL,
	[Total_Amount] [decimal](18, 4) NULL,
	[Update_Time] [datetime] NULL,
	[Remark] [nvarchar](1024) NULL,
	[Reserved1] [nvarchar](50) NULL,
	[Reserved2] [nvarchar](50) NULL,
	[Reserved3] [nvarchar](50) NULL,
 CONSTRAINT [PK_Bill_Of_Arrears] PRIMARY KEY CLUSTERED 
(
	[Unit_Name] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]

GO


