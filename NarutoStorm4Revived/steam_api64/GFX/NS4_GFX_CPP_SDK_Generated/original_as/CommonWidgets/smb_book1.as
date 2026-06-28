package script.net_bingo
{
   import ELoader.ExtendLoader;
   import flash.display.MovieClip;
   import flash.external.ExternalInterface;
   import flash.net.URLRequest;
   import script.icon_rate_m.nut_rate_m;
   import script.xcmn_font.smb_font;
   import script.xcmn_menu.nut_base;
   import script.xcmn_tex00.nut_tex00;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol37")]
   public class smb_book1 extends MovieClip
   {
      
      public var all_base:nut_base;
      
      public var all_rate_m:nut_rate_m;
      
      public var dmy_charicon_l:nut_tex00;
      
      public var dmy_name_m:nut_tex00;
      
      public var mc_base1:MovieClip;
      
      public var nut_icon_cross:MovieClip;
      
      public var txt_title:smb_font;
      
      private var m_iconLoader:ExtendLoader = new ExtendLoader();
      
      private var m_nameLoader:ExtendLoader = new ExtendLoader();
      
      private var m_dmyIcon:MovieClip = null;
      
      private var m_dmyName:MovieClip = null;
      
      private var m_iconPath:String = "";
      
      private var m_namePath:String = "";
      
      private var m_isDowned:Boolean = false;
      
      private var m_itemMsgId:String = "";
      
      private var m_itemNum:int = 0;
      
      private var m_categoryNo:int = 0;
      
      private var m_xfbinname:String = "";
      
      private var m_title:smb_font = null;
      
      public function smb_book1()
      {
         super();
         addFrameScript(0,this.frame1,1,this.frame2,2,this.frame3,3,this.frame4,9,this.frame10,10,this.frame11);
         this.m_dmyIcon = this["dmy_charicon_l"];
         this.m_dmyName = this["dmy_name_m"];
         this.m_title = this["txt_title"];
         this.m_title.SetText(String(ExternalInterface.call("MessageConvert","network_sys_202")));
         gotoAndStop("off");
      }
      
      public function SetIconCode(param1:String) : *
      {
         this.m_iconPath = "../charicon_l/l_" + param1 + ".xfbin";
         trace(this.m_iconPath);
         var _loc2_:URLRequest = new URLRequest(this.m_iconPath);
         this.m_iconLoader.load(_loc2_);
         this.m_dmyIcon.addChild(this.m_iconLoader);
         this.m_iconLoader.SetPivot(ExtendLoader.CCD_PIVOT_CENTER_CENTER);
      }
      
      public function SetReText() : *
      {
         this.m_title.SetText(String(ExternalInterface.call("MessageConvert","network_sys_202")));
      }
      
      public function SetNameCode(param1:String) : *
      {
         this.m_namePath = "../name_m/LANG/nm_" + param1 + ".xfbin";
         trace(this.m_namePath);
         var _loc2_:URLRequest = new URLRequest(this.m_namePath);
         this.m_nameLoader.load(_loc2_);
         this.m_dmyName.addChild(this.m_nameLoader);
         this.m_nameLoader.SetPivot(ExtendLoader.CCD_PIVOT_CENTER_CENTER);
      }
      
      public function SetRare(param1:int) : *
      {
         if(param1 == 0)
         {
            this.mc_base1.gotoAndStop("base_d");
            this.all_rate_m.gotoAndStop("d");
         }
         else if(param1 == 1)
         {
            this.mc_base1.gotoAndStop("base_c");
            this.all_rate_m.gotoAndStop("c");
         }
         else if(param1 == 2)
         {
            this.mc_base1.gotoAndStop("base_b");
            this.all_rate_m.gotoAndStop("b");
         }
         else if(param1 == 3)
         {
            this.mc_base1.gotoAndStop("base_a");
            this.all_rate_m.gotoAndStop("a");
         }
         else if(param1 == 4)
         {
            this.mc_base1.gotoAndStop("base_s");
            this.all_rate_m.gotoAndStop("s");
         }
         else if(param1 == 5)
         {
            this.mc_base1.gotoAndStop("base_s+");
            this.all_rate_m.gotoAndStop("s2");
         }
      }
      
      public function SetDowned() : *
      {
         this.m_isDowned = true;
         gotoAndPlay("comp_loop");
      }
      
      public function GetDowned() : Boolean
      {
         return this.m_isDowned;
      }
      
      public function SetItemInfo(param1:String, param2:int, param3:int, param4:String) : *
      {
         this.m_itemMsgId = param1;
         this.m_itemNum = param2;
         this.m_categoryNo = param3;
         this.m_xfbinname = param4;
      }
      
      public function IsLoaded() : Boolean
      {
         return this.m_iconLoader.IsLoadedXfbin() && this.m_nameLoader.IsLoadedXfbin();
      }
      
      public function IsDowned() : Boolean
      {
         return currentLabel == "comp_loop" ? true : false;
      }
      
      public function GetIconDataPath() : String
      {
         return this.m_iconPath;
      }
      
      public function GetNameDataPath() : String
      {
         return this.m_namePath;
      }
      
      public function GetItemName() : String
      {
         return this.m_itemMsgId;
      }
      
      public function GetItemNum() : uint
      {
         return this.m_itemNum;
      }
      
      public function GetItemCategoryNo() : uint
      {
         return this.m_categoryNo;
      }
      
      public function GetItemXfbin() : String
      {
         return this.m_xfbinname;
      }
      
      internal function frame1() : *
      {
         stop();
         this.txt_title.SetTextColor(9718306);
         this.txt_title.SetTextSize(50);
         this.txt_title.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_title.SetTextFieldWidth(400);
         this.txt_title.SetTextFit(true);
      }
      
      internal function frame2() : *
      {
         play();
         this.txt_title.SetTextColor(9718306);
         this.txt_title.SetTextSize(50);
         this.txt_title.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_title.SetTextFieldWidth(400);
         this.txt_title.SetTextFit(true);
      }
      
      internal function frame3() : *
      {
         gotoAndPlay("off");
         this.txt_title.SetTextColor(9718306);
         this.txt_title.SetTextSize(50);
         this.txt_title.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_title.SetTextFieldWidth(400);
         this.txt_title.SetTextFit(true);
      }
      
      internal function frame4() : *
      {
         this.txt_title.SetTextColor(9718306);
         this.txt_title.SetTextSize(50);
         this.txt_title.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_title.SetTextFieldWidth(400);
         this.txt_title.SetTextFit(true);
      }
      
      internal function frame10() : *
      {
         stop();
         this.txt_title.SetTextColor(9718306);
         this.txt_title.SetTextSize(50);
         this.txt_title.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_title.SetTextFieldWidth(400);
         this.txt_title.SetTextFit(true);
      }
      
      internal function frame11() : *
      {
         stop();
         this.txt_title.SetTextColor(9718306);
         this.txt_title.SetTextSize(50);
         this.txt_title.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_title.SetTextFieldWidth(400);
         this.txt_title.SetTextFit(true);
      }
   }
}

