object Form2: TForm2
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = 'Download Progress'
  ClientHeight = 206
  ClientWidth = 401
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  Position = poMainFormCenter
  OnCloseQuery = FormCloseQuery
  TextHeight = 15
  object BtnCancel: TButton
    Left = 8
    Top = 175
    Width = 384
    Height = 25
    Cancel = True
    Caption = 'Cancel'
    Default = True
    ImageIndex = 3
    ImageMargins.Left = 5
    Images = Form1.ImageList1
    ModalResult = 2
    TabOrder = 0
    OnClick = BtnCancelClick
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 8
    Width = 185
    Height = 81
    Caption = 'Current Track Info'
    DefaultHeaderFont = False
    HeaderFont.Charset = DEFAULT_CHARSET
    HeaderFont.Color = clWindowText
    HeaderFont.Height = -12
    HeaderFont.Name = 'Segoe UI'
    HeaderFont.Style = [fsBold]
    TabOrder = 1
    object LabelTrack: TLabel
      Left = 10
      Top = 24
      Width = 153
      Height = 15
      AutoSize = False
      Caption = 'LabelTrack'
      EllipsisPosition = epEndEllipsis
    end
    object LabelStatus: TLabel
      Left = 10
      Top = 51
      Width = 153
      Height = 15
      AutoSize = False
      Caption = 'LabelStatus'
    end
  end
  object GroupBox2: TGroupBox
    Left = 8
    Top = 95
    Width = 384
    Height = 74
    Caption = 'Track Progress'
    DefaultHeaderFont = False
    HeaderFont.Charset = DEFAULT_CHARSET
    HeaderFont.Color = clWindowText
    HeaderFont.Height = -12
    HeaderFont.Name = 'Segoe UI'
    HeaderFont.Style = [fsBold]
    TabOrder = 2
    object LabelPercent: TLabel
      Left = 16
      Top = 49
      Width = 68
      Height = 15
      Caption = 'LabelPercent'
    end
    object LabelSpeed: TLabel
      Left = 309
      Top = 49
      Width = 60
      Height = 15
      Alignment = taRightJustify
      BiDiMode = bdLeftToRight
      Caption = 'LabelSpeed'
      ParentBiDiMode = False
    end
    object ProgressBar1: TProgressBar
      Left = 16
      Top = 22
      Width = 353
      Height = 21
      Max = 1000
      TabOrder = 0
    end
  end
  object GroupBox3: TGroupBox
    Left = 207
    Top = 8
    Width = 185
    Height = 81
    Caption = 'Progress'
    DefaultHeaderFont = False
    HeaderFont.Charset = DEFAULT_CHARSET
    HeaderFont.Color = clWindowText
    HeaderFont.Height = -12
    HeaderFont.Name = 'Segoe UI'
    HeaderFont.Style = [fsBold]
    TabOrder = 3
    object LabelCount: TLabel
      Left = 0
      Top = 45
      Width = 185
      Height = 25
      Alignment = taCenter
      AutoSize = False
      Caption = 'LabelCount'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Segoe UI'
      Font.Style = []
      ParentFont = False
    end
    object LabelText1: TLabel
      Left = 0
      Top = 19
      Width = 185
      Height = 21
      Alignment = taCenter
      AutoSize = False
      Caption = 'Completed'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Segoe UI'
      Font.Style = [fsBold]
      ParentFont = False
    end
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 150
    OnTimer = Timer1Timer
    Left = 136
    Top = 32
  end
end
