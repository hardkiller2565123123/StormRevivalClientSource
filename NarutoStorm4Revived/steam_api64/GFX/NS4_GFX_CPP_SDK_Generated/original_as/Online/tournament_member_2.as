package script.freebtl_tonmt
{
   import flash.display.MovieClip;
   
   public class tournament_member
   {
      
      public var part:MovieClip;
      
      public var cpu:Boolean;
      
      public var enterNo:int;
      
      public var id:int;
      
      public var drawNo:int;
      
      public var chara:String;
      
      public var name:String;
      
      public var dead:Boolean;
      
      public var win:int;
      
      public var vis:Boolean;
      
      public var lock:Boolean;
      
      public var userId:String;
      
      public var isNet:Boolean;
      
      internal var obj:Object = new Object();
      
      public function tournament_member()
      {
         super();
         this.clear();
      }
      
      public function clear() : void
      {
         this.part = null;
         this.enterNo = -1;
         this.id = -1;
         this.drawNo = 0;
         this.cpu = false;
         this.chara = "";
         this.name = "";
         this.dead = false;
         this.vis = true;
         this.win = 0;
         this.lock = false;
         this.userId = "";
         this.isNet = false;
      }
      
      public function setUser(param1:tournament_member) : void
      {
         this.setUserPart(param1.part);
         this.setUserData(param1);
         this.updata_mc();
      }
      
      public function setUserPart(param1:MovieClip) : void
      {
         this.part = param1;
      }
      
      public function setUserData(param1:tournament_member) : void
      {
         this.enterNo = param1.id;
         this.id = param1.id;
         this.chara = param1.chara;
         this.name = param1.name;
         this.dead = param1.dead;
         this.win = param1.win;
         this.vis = param1.vis;
         this.cpu = param1.cpu;
         this.userId = param1.userId;
         this.isNet = param1.isNet;
         this.drawNo = param1.drawNo;
      }
      
      public function updata_mc() : void
      {
         if(this.part)
         {
            if(this.chara != null && this.chara != "")
            {
               this.part.clearFace();
               this.part.setFace(this.chara);
            }
            if(this.isNet)
            {
               this.part.setDispName(false);
               this.part.SetUserName(this.userId);
               this.part.setPlayerIcon(this.drawNo + 1 + "P");
               this.part.setPlayerIconVisible(true);
               if(this.vis == false || this.cpu == true)
               {
                  this.part.SetUserName("");
                  this.part.setPlayerIcon("COM");
                  this.AnmDead(false);
                  this.dead = true;
                  this.part.setPlayerIconVisible(false);
               }
            }
            else
            {
               this.part.setDispName(true);
               if(this.name != null && this.name != "")
               {
                  this.part.clearName();
                  this.part.setName(this.name);
               }
               if(this.cpu == true)
               {
                  this.part.setPlayerIcon("COM");
               }
               else
               {
                  this.part.setPlayerIcon(this.drawNo + 1 + "P");
               }
            }
         }
      }
      
      public function finalize() : void
      {
         if(this.part)
         {
            this.part.clearFace();
            this.part.clearName();
         }
      }
      
      public function setDead(param1:Boolean) : void
      {
         this.dead = param1;
      }
      
      public function isLoad() : Boolean
      {
         return this.part.isLoad();
      }
      
      public function getLock() : Boolean
      {
         return this.lock;
      }
      
      public function getDead() : Boolean
      {
         return this.dead;
      }
      
      public function setVisible(param1:Boolean) : void
      {
         this.vis = param1;
      }
      
      public function getVisible() : Boolean
      {
         return this.vis;
      }
      
      public function getID() : int
      {
         return this.id;
      }
      
      public function getEnterNo() : int
      {
         return this.enterNo;
      }
      
      public function setID(param1:Number) : *
      {
         this.id = param1;
      }
      
      public function getDrawNo(param1:Number) : *
      {
         return this.drawNo;
      }
      
      public function getWin() : int
      {
         return this.win;
      }
      
      public function getChara() : String
      {
         return this.chara;
      }
      
      public function AddWin() : void
      {
         ++this.win;
      }
      
      public function setWin() : void
      {
         --this.win;
      }
      
      public function AnmDead(param1:Boolean) : void
      {
         if(this.part)
         {
            this.part.setDark(param1,true);
         }
      }
      
      public function AnmSelect(param1:Boolean, param2:Boolean) : void
      {
         if(this.part != null)
         {
            this.part.setSelect(param1,param2);
         }
      }
   }
}

