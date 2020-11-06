USE [NHMFDServerDB]
GO

/****** Object:  Table [dbo].[Charge_log_record]    Script Date: 07/14/2020 20:35:47 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[Charge_log_record](
	[AutoID] [int] IDENTITY(1,1) NOT NULL,
	[Times] [datetime] NULL, 
	[Description] [nvarchar](1024) NULL,
	[Remark] [nvarchar](1024) NULL,
	[Reserved1] [nvarchar](50) NULL,
	[Reserved2] [nvarchar](50) NULL,
	[Reserved3] [nvarchar](50) NULL,
 CONSTRAINT [PK_CHARGE_LOG_RECORD] PRIMARY KEY CLUSTERED 
(
	[AutoID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]

GO