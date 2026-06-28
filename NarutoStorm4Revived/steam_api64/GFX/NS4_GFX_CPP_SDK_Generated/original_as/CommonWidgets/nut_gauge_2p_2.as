package script.gauge_p
{
   import ELoader.ExtendLoader;
   import Enum.Enum;
   import flash.display.DisplayObject;
   import flash.display.MovieClip;
   import flash.net.URLRequest;
   import script.gauge_awk.nut_awk;
   import script.gauge_awk.nut_awk_lock;
   import script.gauge_cmn.anm_eff_ckr;
   import script.gauge_cmn.nut_ckr;
   import script.gauge_cmn.nut_kwrm;
   import script.gauge_cmn.nut_life;
   import script.gauge_cmn.nut_main_bg1;
   import script.gauge_plat.nut_btn;
   import script.xcmn_tex00.nut_tex00;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol12")]
   public class nut_gauge_2p extends MovieClip
   {
      
      public static const CCD_MEMBER_NUM:int = 3;
      
      public var all_awk:nut_awk;
      
      public var all_bg:nut_main_bg1;
      
      public var all_ckr:nut_ckr;
      
      public var all_eff_awk:anm_eff_ckr;
      
      public var all_eff_awk1:MovieClip;
      
      public var all_eff_ckr:anm_eff_ckr;
      
      public var all_gauge_btn:nut_btn;
      
      public var all_kwrm:nut_kwrm;
      
      public var all_life:nut_life;
      
      public var all_lock:nut_awk_lock;
      
      public var dmy_char:nut_tex00;
      
      public var dmy_name:nut_tex00;
      
      public var mc_team:all_team;
      
      private const CCD_TEAM_GAUGE_NORMAL:int = Enum.Next(0);
      
      private const CCD_TEAM_GAUGE_HALF:int = Enum.Next();
      
      private const CCD_TEAM_GAUGE_MAX:int = Enum.Next();
      
      public var GetFaceIconName:Function;
      
      public var GetAwakeIconName:Function;
      
      public var GetNameIconName:Function;
      
      public var GetDodgeKeyName:Function;
      
      public var IsAwakeLeader:Function;
      
      private var m_loaderFace:Array = new Array(3);
      
      private var m_loaderAwake:Array = new Array(3);
      
      private var m_loaderName:Array = new Array(3);
      
      private var m_loaderPairAwake:ExtendLoader;
      
      private var m_loaderPairName:ExtendLoader;
      
      private var m_faceNum:int;
      
      private var m_nameNum:int;
      
      private var m_effChakra:MovieClip;
      
      private var m_effAwake:MovieClip;
      
      private var m_effTeam:MovieClip;
      
      private var m_allBg:MovieClip;
      
      private var m_teamGaugeState:int;
      
      private var m_isNetwork:* = false;
      
      private var m_side:int = 1;
      
      public function nut_gauge_2p()
      {
         super();
         addFrameScript(0,this.frame1,16,this.frame17,32,this.frame33);
         var _loc1_:int = 0;
         while(_loc1_ < CCD_MEMBER_NUM)
         {
            this.m_loaderFace[_loc1_] = new ExtendLoader();
            this.m_loaderAwake[_loc1_] = new ExtendLoader();
            this.m_loaderName[_loc1_] = new ExtendLoader();
            _loc1_++;
         }
      }
      
      public function Initialize() : *
      {
         this.m_teamGaugeState = this.CCD_TEAM_GAUGE_NORMAL;
         this.m_isNetwork = false;
         this.m_effChakra = MovieClip(getChildByName("all_eff_ckr"));
         this.SetChakraCharge(false);
         this.m_effAwake = MovieClip(getChildByName("all_eff_awk"));
         this.SetAwakeEffect(false);
         this.m_effTeam = MovieClip(getChildByName("all_eff_awk1"));
         this.SetTeamGaugeHalfEffect(false);
         this.m_allBg = MovieClip(getChildByName("all_bg"));
         this["all_gauge_btn"].gotoAndStop(this.GetDodgeKeyName(this.m_side));
         this.LoadIcon();
         this.SetFaceIcon(0);
         this.SetNameIcon(0);
      }
      
      public function Finalize() : *
      {
         var _loc1_:int = 0;
         while(_loc1_ < CCD_MEMBER_NUM)
         {
            this.m_loaderFace[_loc1_].unload();
            this.m_loaderAwake[_loc1_].unload();
            this.m_loaderName[_loc1_].unload();
            _loc1_++;
         }
         if(this.m_loaderPairAwake)
         {
            this.m_loaderPairAwake.unload();
         }
         if(this.m_loaderPairName)
         {
            this.m_loaderPairName.unload();
         }
      }
      
      public function SetVisible(param1:Boolean) : *
      {
         this.visible = param1;
      }
      
      public function SetEnableChakraGauge(param1:Boolean) : *
      {
      }
      
      public function SetChakraCharge(param1:Boolean) : *
      {
         if(this.m_effChakra)
         {
            this.m_effChakra.visible = param1;
         }
      }
      
      public function SetAwakeEffect(param1:Boolean, param2:Boolean = false) : *
      {
         var _loc3_:nut_awk = null;
         if(this.m_effAwake)
         {
            this.m_effAwake.visible = param1;
         }
         if(param1)
         {
            this.SetTeamGaugeHalfEffect(false);
            if(this.m_allBg)
            {
               this.m_allBg.gotoAndPlay("awk2");
            }
         }
         else
         {
            _loc3_ = nut_awk(this["all_awk"]);
            switch(this.m_teamGaugeState)
            {
               case this.CCD_TEAM_GAUGE_NORMAL:
                  this.SetTeamGaugeHalfEffect(false);
                  if(this.m_allBg)
                  {
                     this.m_allBg.gotoAndStop("loop");
                  }
                  if(_loc3_)
                  {
                     _loc3_.ChangeGaugeType(nut_awk.CCD_AWAKE_GAUGE_NORMAL,param2);
                  }
                  break;
               case this.CCD_TEAM_GAUGE_HALF:
                  this.SetTeamGaugeHalfEffect(true);
                  if(this.m_allBg)
                  {
                     this.m_allBg.gotoAndPlay("awk1");
                  }
                  if(_loc3_)
                  {
                     _loc3_.ChangeGaugeType(nut_awk.CCD_AWAKE_GAUGE_NORMAL,param2);
                  }
                  break;
               case this.CCD_TEAM_GAUGE_MAX:
                  this.SetTeamGaugeHalfEffect(false);
                  if(this.m_allBg)
                  {
                     this.m_allBg.gotoAndPlay("awk2");
                  }
                  if(_loc3_)
                  {
                     _loc3_.ChangeGaugeType(nut_awk.CCD_AWAKE_GAUGE_TEAM,param2);
                  }
            }
         }
      }
      
      private function SetTeamGaugeHalfEffect(param1:Boolean) : *
      {
         if(Boolean(this.m_effTeam) && this["mc_team"].visible == true)
         {
            if(this.m_effTeam.visible != param1 && this.m_effTeam.visible == false)
            {
               this.m_effTeam.gotoAndPlay(1);
            }
            this.m_effTeam.visible = param1;
         }
      }
      
      public function SetTeamGaugeRate(param1:Number) : *
      {
         var _loc5_:nut_awk = null;
         if(this["mc_team"].visible == false)
         {
            return;
         }
         var _loc2_:Number = 0.5;
         var _loc3_:Number = 1;
         var _loc4_:int = this.m_teamGaugeState;
         if(param1 >= _loc3_)
         {
            this.m_teamGaugeState = this.CCD_TEAM_GAUGE_MAX;
         }
         else if(param1 >= _loc2_)
         {
            this.m_teamGaugeState = this.CCD_TEAM_GAUGE_HALF;
         }
         else
         {
            this.m_teamGaugeState = this.CCD_TEAM_GAUGE_NORMAL;
         }
         if(_loc4_ != this.m_teamGaugeState)
         {
            if(this.m_effAwake.visible == true)
            {
               if(this.m_allBg)
               {
                  this.m_allBg.gotoAndPlay("awk2");
               }
            }
            else
            {
               _loc5_ = nut_awk(this["all_awk"]);
               switch(this.m_teamGaugeState)
               {
                  case this.CCD_TEAM_GAUGE_NORMAL:
                     this.SetTeamGaugeHalfEffect(false);
                     if(this.m_allBg)
                     {
                        this.m_allBg.gotoAndStop("loop");
                     }
                     if(_loc5_)
                     {
                        _loc5_.ChangeGaugeType(nut_awk.CCD_AWAKE_GAUGE_NORMAL);
                     }
                     break;
                  case this.CCD_TEAM_GAUGE_HALF:
                     this.SetTeamGaugeHalfEffect(true);
                     if(this.m_allBg)
                     {
                        this.m_allBg.gotoAndPlay("awk1");
                     }
                     if(_loc5_)
                     {
                        _loc5_.ChangeGaugeType(nut_awk.CCD_AWAKE_GAUGE_NORMAL);
                     }
                     break;
                  case this.CCD_TEAM_GAUGE_MAX:
                     this.SetTeamGaugeHalfEffect(false);
                     if(this.m_allBg)
                     {
                        this.m_allBg.gotoAndPlay("awk2");
                     }
                     if(_loc5_)
                     {
                        _loc5_.ChangeGaugeType(nut_awk.CCD_AWAKE_GAUGE_TEAM);
                     }
               }
            }
         }
      }
      
      public function SetEnableKawarimiGauge(param1:Boolean) : *
      {
         this["all_kwrm"].visible = param1;
         this["all_gauge_btn"].visible = param1;
      }
      
      public function SetEnableTeamGauge(param1:Boolean) : *
      {
         this["mc_team"].visible = param1;
      }
      
      public function SetEnableAwakeGauge(param1:Boolean) : *
      {
         this["all_awk"].visible = param1;
         this["all_lock"].visible = param1;
      }
      
      public function LoadIcon() : *
      {
         var _loc5_:String = null;
         var _loc6_:String = null;
         var _loc7_:String = null;
         var _loc8_:URLRequest = null;
         var _loc9_:URLRequest = null;
         var _loc10_:URLRequest = null;
         this.m_faceNum = 0;
         this.m_nameNum = 0;
         var _loc1_:int = 0;
         while(_loc1_ < CCD_MEMBER_NUM)
         {
            _loc5_ = String(this.GetFaceIconName(this.m_side,_loc1_));
            if(_loc5_ == "" && _loc1_ == 0)
            {
               _loc5_ = "xxx1";
            }
            if(_loc5_ != "")
            {
               _loc8_ = new URLRequest("../charicon_p/p_" + _loc5_ + ".xfbin");
               this.m_loaderFace[_loc1_].load(_loc8_);
               this.m_loaderFace[_loc1_].SetPivot(ExtendLoader.CCD_PIVOT_CENTER_CENTER);
               ++this.m_faceNum;
            }
            _loc6_ = String(this.GetAwakeIconName(this.m_side,_loc1_));
            if(_loc6_ != "")
            {
               _loc9_ = new URLRequest("../charicon_p/p_" + _loc6_ + ".xfbin");
               this.m_loaderAwake[_loc1_].load(_loc9_);
               this.m_loaderAwake[_loc1_].SetPivot(ExtendLoader.CCD_PIVOT_CENTER_CENTER);
            }
            _loc7_ = String(this.GetNameIconName(this.m_side,_loc1_));
            if(_loc7_ == "" && _loc1_ == 0)
            {
               _loc7_ = "xxx1";
            }
            if(_loc7_ != "")
            {
               _loc10_ = new URLRequest("../name_m/LANG/nm_" + _loc7_ + ".xfbin");
               this.m_loaderName[_loc1_].load(_loc10_);
               this.m_loaderName[_loc1_].SetPivot(ExtendLoader.CCD_PIVOT_CENTER_RIGHT);
               ++this.m_nameNum;
            }
            _loc1_++;
         }
         var _loc2_:int = 0;
         while(_loc2_ < this.m_faceNum)
         {
            this["dmy_char"].addChild(this.m_loaderFace[_loc2_]);
            _loc2_++;
         }
         var _loc3_:int = 0;
         while(_loc3_ < this.m_faceNum)
         {
            this["dmy_char"].addChild(this.m_loaderAwake[_loc3_]);
            _loc3_++;
         }
         var _loc4_:int = 0;
         while(_loc4_ < this.m_nameNum)
         {
            this["dmy_name"].addChild(this.m_loaderName[_loc4_]);
            _loc4_++;
         }
      }
      
      public function SetFaceIcon(param1:int) : *
      {
         var _loc2_:int = 0;
         while(_loc2_ < this.m_faceNum)
         {
            DisplayObject(this.m_loaderFace[_loc2_]).visible = false;
            DisplayObject(this.m_loaderAwake[_loc2_]).visible = false;
            _loc2_++;
         }
         if(this.IsAwakeLeader(this.m_side))
         {
            DisplayObject(this.m_loaderAwake[param1]).visible = true;
         }
         else
         {
            DisplayObject(this.m_loaderFace[param1]).visible = true;
         }
      }
      
      public function SetNameIcon(param1:int) : *
      {
         if(this.m_isNetwork == true)
         {
            return;
         }
         var _loc2_:int = 0;
         while(_loc2_ < this.m_nameNum)
         {
            DisplayObject(this.m_loaderName[_loc2_]).visible = false;
            _loc2_++;
         }
         DisplayObject(this.m_loaderName[param1]).visible = true;
      }
      
      public function SetNetwork() : *
      {
         this.m_isNetwork = true;
         var _loc1_:int = 0;
         while(_loc1_ < this.m_nameNum)
         {
            DisplayObject(this.m_loaderName[_loc1_]).visible = false;
            _loc1_++;
         }
      }
      
      public function SetForSimpleUI(param1:Number, param2:Number) : *
      {
         this.x = param1;
         this.y = param2;
         this.SetEnableKawarimiGauge(false);
         this.SetEnableTeamGauge(false);
      }
      
      public function ResetGaugeInputPad() : *
      {
         this["all_gauge_btn"].gotoAndStop(this.GetDodgeKeyName(this.m_side));
      }
      
      public function CreatePairAwake() : *
      {
         this.m_loaderPairAwake = new ExtendLoader();
         var _loc1_:URLRequest = new URLRequest("../charicon_p/p_sks1.xfbin");
         this.m_loaderPairAwake.load(_loc1_);
         this.m_loaderPairAwake.SetPivot(ExtendLoader.CCD_PIVOT_CENTER_CENTER);
         this.m_loaderPairAwake.visible = false;
         this["dmy_char"].addChild(this.m_loaderPairAwake);
         this.m_loaderPairName = new ExtendLoader();
         var _loc2_:URLRequest = new URLRequest("../name_m/LANG/nm_nxs1.xfbin");
         this.m_loaderPairName.load(_loc2_);
         this.m_loaderPairName.SetPivot(ExtendLoader.CCD_PIVOT_CENTER_RIGHT);
         this.m_loaderPairName.visible = false;
         this["dmy_name"].addChild(this.m_loaderPairName);
      }
      
      public function SetPairAwake(param1:Boolean) : *
      {
         var _loc2_:int = 0;
         if(param1)
         {
            _loc2_ = 0;
            while(_loc2_ < this.m_faceNum)
            {
               DisplayObject(this.m_loaderFace[_loc2_]).visible = false;
               DisplayObject(this.m_loaderAwake[_loc2_]).visible = false;
               DisplayObject(this.m_loaderName[_loc2_]).visible = false;
               _loc2_++;
            }
            this.m_loaderPairAwake.visible = true;
            if(this.m_isNetwork == false)
            {
               this.m_loaderPairName.visible = true;
            }
         }
         else
         {
            this.m_loaderPairAwake.visible = false;
            this.m_loaderPairName.visible = false;
         }
      }
      
      internal function frame1() : *
      {
         this.stop();
      }
      
      internal function frame17() : *
      {
         gotoAndStop("loop");
      }
      
      internal function frame33() : *
      {
         gotoAndStop("loop");
      }
   }
}

